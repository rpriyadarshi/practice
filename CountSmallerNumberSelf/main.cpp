#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <locale>
#include <sstream>
#include <cassert>

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return ch != '[';
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return ch != ']';
    }).base(), s.end());
}

class Solution {
public: // Alias
    using IntPair = std::pair<int, int>;
    using IntPairVec = std::vector<IntPair>;
    using IntVec = std::vector<int>;
public: // Data
    IntPairVec _nums;
    IntVec _res;

public:
    static void print(const IntVec& vals) {
        std::cout << "[";
        int i = 0;
        for (; i < vals.size() - 1; i++) {
            std::cout << vals[i] << ",";
        }
        std::cout << vals[i];
        std::cout << "]" << std::endl;
    }
    static void print(const IntPairVec& pairs, int l, int r) {
        std::cout << "[";
        int i = l;
        for (; i < r; i++) {
            std::cout << pairs[i].first << ",";
        }
        std::cout << pairs[i].first;
        std::cout << "]";
    }
    std::vector<int> countSmallerN2(std::vector<int>& nums) {
        std::vector<int> res;
        res.resize(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                res[i] += nums[i] > nums[j];
            }
        }
//        print(res);
        std::cout << std::endl;
        return res;
    }

    void merge(int l1, int l2, int r1, int r2) {
        int len = l2 - l1 + 1 + r2 - r1 + 1;
//        std::cout << "[(" << l1 << ", " << l2 << "), (" << r1 << ", " << r2 << ")]=" << len << " -- ";
        if (_nums[l2].first >= _nums[r1].first) { // Already sorted
            for (int l = l1; l <= l2; l++) {
                _res[_nums[l].second] += (r2 - r1 + 1);
            }
        } else {
            IntPairVec temp(len);
            int l = l1;
            int r = r1;
            for (int i = 0; i < len; i++) {
                if (l > l2) {
                    if (r > r2) {
                        std::cout << std::endl;
                    } else {
                        temp[i] = _nums[r++];
                    }
                } else {
                    if (r > r2) {
                        temp[i] = _nums[l++];
                    } else {
                        int n1 = _nums[l].first;
                        int n2 = _nums[r].first;
                        if (n1 > n2) {
                            _res[_nums[l].second] += (r2 - r + 1);
                            temp[i] = _nums[l++];
                        } else {
                            temp[i] = _nums[r++];
                        }
                    }
                }
            }
            int j = 0;
            for (l = l1; l <= l2; l++) {
                _nums[l] = temp[j++];
            }
            for (r = r1; r <= r2; r++) {
                _nums[r] = temp[j++];
            }
        }
//        print(_nums, l1, l2);
//        print(_nums, r1, r2);
//        std::cout << std::endl;
    }
    void sort(int l, int r) {
        if (l < r) {
            int mid = l + (r - l) / 2;

            sort(l, mid);
            sort(mid + 1, r);
            merge(l, mid, mid + 1, r);
        } else {
        }
    }
    std::vector<int> countSmaller(std::vector<int>& nums) {
        _res.resize(nums.size());
        _nums.resize(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            _nums[i] = std::move(IntPair(nums[i], i));
        }
        // Merge sort
        sort(0, nums.size() - 1);

//        print(_nums, 0, _nums.size() - 1);
//        std::cout << std::endl;
//        print(_res);
//        std::cout << std::endl;
        return _res;
    }
};

int main(int argc, const char** argv) {
    if (argv[1] == nullptr) {
        std::cout << "Missing filename" << std::endl;
        return 1;
    }
    const std::string filename(argv[1]);
    std::ifstream ifstr(filename);
    std::string str;
    if (ifstr.good()) {
        ifstr >> str;
    }

    ltrim(str);
    rtrim(str);
    std::istringstream istrstr(str);
    std::vector<int> data;
    while (istrstr.good()) {
        std::string numStr;
        std::getline(istrstr, numStr, ',');
        data.push_back(std::stoi(numStr));
    }

    Solution sol;
    std::cout << "O(N.lg(N)) solution ..." << std::endl;
    std::vector<int> resNlg2 = std::move(sol.countSmaller(data));
    std::cout << "O(N^2) solution ..." << std::endl;
    std::vector<int> resN2 = std::move(sol.countSmallerN2(data));
    std::cout << "done" << std::endl;

    // Verification
    assert(resNlg2.size() == resN2.size());
    std::sort(data.begin(), data.end(), std::greater<>());
//    Solution::print(data);
//    Solution::print(sol._nums, 0, sol._nums.size() - 1);
//    std::cout << std::endl;

    bool error = false;
    for (int i = 0; i < resN2.size() && !error; i++) {
        if (data[i] != sol._nums[i].first) {
            std::cout << "ERROR! Sorting mismatch found! " << resN2[i] << " != " << resNlg2[i] << std::endl;
            error = true;
        }
    }
    error = false;
    for (int i = 0; i < resN2.size() && !error; i++) {
        if (resN2[i] != resNlg2[i]) {
            std::cout << "ERROR! Count mismatch found! " << resN2[i] << " != " << resNlg2[i] << std::endl;
            error = true;
        }
    }
    return 0;
}
