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

[7,40,10,10,40,39,96,21,54,73,33,17,2,72,5,76,28,73,59,22,100,91,80,66,5,49,26,45,13,27,74,87,56,76,25,64,14,86,50,38,65,64,3,42,79,52,37,3,21,26,42,73,18,44,55,28,35,87]
63

[477,2431,4099,3624,9221,2186,1848,3025,6736,821,1626,8941,4354,1753,3348,4288,1095,9359,8625,1287,1193,3562,2841,8381,7080,358,9673,6032,7974,4649,3604,3284,9799,8088,3854,6971,7409,6016,8921,3094,7900,1192,4204,6674,3300,136,8717,6238,8427,7981,1252,6615,8357,9475,9579,6973,658,5765,7512,105,3110,4905,91,8861,1967,4959,8397,5171,8897,9372,9034,4629,8612,6741,8881,8485,6690,9876,9521,5043,7415,4947,2146,8296,7278,9606,2300,9012,2671,4141,158,6950,9272,594,6036,6896,6589,4613,301,1483,1476,79,6282,4406,7609,4456,6106,7888,5514,6365,7474,1909,7926,5809,2371,6803,2430,298,2820,4264,6026,2083,9660,4705,6766,4226,8418,4707,6894,4484,7103,5504,7960,3531,8051,6585,6966,1498,1056,2122,3378,2452,3756,429,1692,4149,2552,7861,1622,6540,3071,50,1461,7008,834,9005,3577,8758,6913,5681,771,1691,9058,6876,1944,4348,4568,2934,7860,782,3510,1429,6386,2029,7329,4821,8321,8159,6441,1904,9931,7852,1734,2444,6331,3297,2739,8532,4221,6826,8794,4729,8069,8926,3517,5523,7963,1686,141,5684,4384,925,8857,7214,4913,1651,3745,8324,4499,4430,4037,6745,2431,2134,4200,3200,6681,9189,9806,958,8730,9978,8346,2439,6780,4427,4585,7867,5011,4376,8050,3513,8172,6025,9815,7710,3960,5545,2887,9925,2969,9512,7392,8762,2449,953,8257,5342,8659,2213,3493,5167,8090,7871,5408,1940,2096,2296,4202,3687,1443,8829,820,9226,2820,1903,3707,9229,3268,8242,9300,5045,6919,5369,70,329,5003,3609,1386,3679,4591,5589,4409,9850,8494,6215,379,1994,5405,5686,2285,1858,4110,2348,9405,673,5686,1268,1505,1691,4915,5195,4079,4413,8678,816,5928,511,1284,2278,6543,6096,3966,1538,5388,4484,131,8442,5273,1839,5774,2063,9932,4442,6639,1493,9448,8647,7792,9248,6861,8778,6452,4934,3595,4959,8997,2182,884,9832,8332,1801,2870,3942,3523,7121,4498,8945,328,4103,8829,4439,8686,4289,7754,2066,6608,1700,6120,1132,8917,5950,8926,9102,8313,9517,499,5049,7299,2167,2553,1219,9491,2326,3544,7932,5497,5982,4790,2618,2550,6255,7205,6647,1932,9847,2379,4420,4839,9891,135,8803,159,2173,6218,9207,1658,7529,498,7078,9807,6919,4524,6065,6692,6655,9926,7570,873,1626,7713,613,10,690,1821,9624,2287,8691,8325,5838,9029,4439,9310,5840,7765,4017,3930,1730,9214,5861,2600,1908,665,5140,6921,5674,4154,913,7125,6799,6166,5878,4816,5591,7226,3901,9989,8504,2366,919,5596,1860,8406,2822,8898,7987,5587,1991,9549,355,7869,3428,6279,2863,6509,3733,1634,4070,5499,5392,4017,7559,7720,6055,8072,3175,7078,7219,6535,8881,1973,9363,8000,4366,2052,2456,196,6163,6794,1786,430,1223,2998,7517,6178,8226,4727,2548,2528,8596,1733,4172,308,7610,6498,3742,8811,6403,88,8915,4088,6930,2604,2934,5612,3919,1247,8788,9140,2637,2878,6156,9591,354,8407,3554,7003,3862,663,8449,3117,8259,8795,1266,4062,6524,7618,1952,9290,793,6341,1470,9175,1550,7847,737,8495,3919,200,342,5112,7642,4556,6809,2732,9748,2183,9203,5216,8761,7352,8219,6843,9074,2747,6480,6375,3289,8117,4562,5899,2482,4251,9288,4580,2870,1371,5907,5507,2339,4235,4179,4134,5724,6296,4574,9265,7664,221,2442,2135,4141,3702,3220,1155,9493,8808,3251,8897,7033,3930,9464,2281,9076,7545,6412,3209,1353,1265,2509,943,496,6642,6269,6837,2253,9684,9780,2117]
6374

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
//                    nextMinIdx = s;
//                } else {
//                    l = maxIdx + 1;
//                    maxIdx = nextMaxIdx;
//                    nextMaxIdx = s;
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
