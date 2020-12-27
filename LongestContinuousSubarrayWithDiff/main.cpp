#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <locale>
#include <sstream>
#include <cassert>
#include <queue>
/*
[24,12,71,33,5,87,10,11,3,58,2,97,97,36,32,35,15,80,24,45,38,9,22,21,33,68,22,85,35,83,92,38,59,90,42,64,61,15,4,40,50,44,54,25,34,14,33,94,66,27,78,56,3,29,3,51,19,5,93,21,58,91,65,87,55,70,29,81,89,67,58,29,68,84,4,51,87,74,42,85,81,55,8,95,39]
87

[1,5,2,1,6,7,9,5,9,1,6]
4

[4,2,2,2,4,4,2,2]
0

[8,2,4,7]
4

[10,1,2,4,7,2]
5

[1,5,6,7,8,10,6,5,6]
4
*/

class Solution {
public:
    int longestSubarray(std::vector<int>& nums, int limit) {
        std::deque<int> minq;
        std::deque<int> maxq;
        minq.push_back(0);
        maxq.push_back(0);
        int maxSize = 1;
        int l = 0;
        for (int r = 1; r < nums.size(); r++) {
            while (!minq.empty() && nums[minq.back()] >= nums[r]) {
                minq.pop_back();
            }
            minq.push_back(r);
            while (!maxq.empty() && nums[maxq.back()] <= nums[r]) {
                maxq.pop_back();
            }
            maxq.push_back(r);

            int diff = nums[maxq.front()] - nums[minq.front()];
//            int diff1 = abs(nums[minq.front()] - nums[r]);
//            int diff2 = abs(nums[maxq.front()] - nums[r]);
//            std::cout << r << " [" << nums[r] << " [" << nums[maxq.front()] << ", " << nums[minq.front()] << "]] ";
//            std::cout << diff << "(" << diff1 << "," << diff2 << ")";
            if (diff > limit) {
                if (minq.front() < maxq.front()) {
                    l = minq.front() + 1;
                    minq.pop_front();
                } else {
                    l = maxq.front() + 1;
                    maxq.pop_front();
                }
            }
            maxSize = std::max(maxSize, r - l + 1);
//            std::cout << "[" << r - l + 1 << "," << maxSize << "]" << std::endl;
        }
        return maxSize;
    }

    int longestSubarrayMine(std::vector<int>& nums, int limit) {
        int maxSize = 0;

        int l = 0;
        int s = 1;
        int minIdx = l;
        int maxIdx = l;
        int nextMinIdx = l;
        int nextMaxIdx = l;
        for (int r = 0; r < nums.size(); r++, s++) {
            s = std::min(s, int(nums.size() - 1));
            if (nums[minIdx] >= nums[r]) {
                minIdx = r;
                nextMinIdx = s;
            }
            if (nums[maxIdx] <= nums[r]) {
                maxIdx = r;
                nextMaxIdx = s;
            }

            if (nums[nextMinIdx] >= nums[s]) {
                nextMinIdx = s;
            }
            if (nums[nextMaxIdx] <= nums[s]) {
                nextMaxIdx = s;
            }

            int diff = abs(nums[maxIdx] - nums[minIdx]);
//            int diff1 = abs(nums[minIdx] - nums[r]);
//            int diff2 = abs(nums[maxIdx] - nums[r]);
//            std::cout << r << " [" << nums[r] << " [" << nums[maxIdx] << ", " << nums[minIdx] << "]] ";
//            std::cout << diff << "(" << diff1 << "," << diff2 << ")";
            if (diff > limit) {
//                if (minIdx < maxIdx) {
//                    l = minIdx + 1;
//                    minIdx = nextMinIdx;
//                } else {
//                    l = maxIdx + 1;
//                    maxIdx = nextMaxIdx;
//                }

                l = std::min(maxIdx, minIdx) + 1;
                minIdx = l;
                maxIdx = l;
                for (int i = l; i <= r; i++) {
                    if (nums[minIdx] >= nums[i]) {
                        minIdx = i;
                    }
                    if (nums[maxIdx] <= nums[i]) {
                        maxIdx = i;
                    }
                }
            }

            maxSize = std::max(maxSize, r - l + 1);
//            std::cout << "[" << r - l + 1 << "," << maxSize << "]" << std::endl;
        }
        return maxSize;
    }
};

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

int main(int argc, const char** argv) {
    if (argv[1] == nullptr) {
        std::cout << "Missing filename" << std::endl;
        return 1;
    }
    const std::string filename(argv[1]);
    std::ifstream ifstr(filename);
    std::string str;
    int limit = 0;
    if (ifstr.good()) {
        ifstr >> str;
        ifstr >> limit;
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
    std::cout << sol.longestSubarrayMine(data, limit) << std::endl;
    std::cout << sol.longestSubarray(data, limit) << std::endl;

    return 0;
}
