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
*/

class Solution {
public:
    int longestSubarray(std::vector<int>& nums, int limit) {
        int maxSize = 0;

        int l = 0;
        int minIdx = l;
        int maxIdx = l;
        for (int r = 0; r < nums.size(); r++) {
            if (nums[minIdx] >= nums[r]) {
                minIdx = r;
            }
            if (nums[maxIdx] <= nums[r]) {
                maxIdx = r;
            }

            int diff = abs(nums[maxIdx] - nums[minIdx]);
            int diff1 = abs(nums[minIdx] - nums[r]);
            int diff2 = abs(nums[maxIdx] - nums[r]);
            std::cout << "[" << nums[r] << ", " << nums[maxIdx] << ", " << nums[minIdx] << "] ";
            std::cout << diff << "(" << diff1 << "," << diff2 << ")";
            if (diff > limit) {
                l = std::min(r, minIdx + 1);
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
            std::cout << "[" << r - l + 1 << "," << maxSize << "]" << std::endl;
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
    std::cout << sol.longestSubarray(data, limit) << std::endl;

    return 0;
}
