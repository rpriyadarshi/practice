//
//  main.cpp
//  2Sum
//
//  Created by Rohit Priyadarshi on 9/26/18.
//  Copyright © 2018 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <unordered_set>

typedef std::vector<long> LongVec;
typedef std::unordered_set<long> LongUSet;
typedef std::set<long> LongSet;
typedef std::map<long, long> LongMap;

void loadData(const std::string& filename, LongVec& vec) {
    std::ifstream istrm(filename);
    if (!istrm.is_open()) {
        std::cout << "failed to open " << filename << '\n';
    } else {
        long v;
        while (istrm >> v) {
            vec.push_back(v);
        }
    }
}

void compute2Sum(LongVec& vec, LongUSet& tset, long t, LongUSet& rset) {
    for (auto x : vec) {
        long y = t - x;
        if (x == y) {
            continue;
        }

        auto tf = tset.find(y);
        if (tf != tset.end()) {
            rset.insert(t);
        }
    }
}

void compute2Sum(LongVec& vec, long min, long max) {
    LongUSet tset(vec.begin(), vec.end());
    LongUSet rset;
    for (long t = min; t <= max; t++) {
        compute2Sum(vec, tset, t, rset);
    }
    std::cout << rset.size() << std::endl;
}

enum Affinity {EQ, GEQ, LEQ};

long binarySearch(LongVec& vec, long val, long min, long max, enum Affinity af) {
    long l = 0;
    long r = vec.size() - 1;
    
    long m = -1;
    long pm = m;
    while (1) {
        pm = m;
        m = l + (r - l) / 2;
        if (pm == m) {
            break;
        }
        
        if (val < vec[m]) {
            r = m;
        } else if (val > vec[m]) {
            l = m;
        } else {
            break;
        }
    }
    
    long idx = -1;
    
    switch (af) {
        case EQ:
            idx = (val == vec[m]) ? m : -1;
            break;
        case GEQ:
            idx = (val == vec[m]) ? m : r;
            break;
        case LEQ:
            idx = (val == vec[m]) ? m : l;
            break;
        default:
            idx = -1;
            break;
    }
    return idx;
}

void computeFast2Sum(LongVec& vec, long min, long max) {
    std::sort(vec.begin(), vec.end());
    LongMap tmap;
    for (long i = 0; i < vec.size(); i++) {
        long v = vec[i];
        tmap[v] = i;
    }
    LongUSet rset;
    for (auto x : vec) {
        long ymin = min - x;
        long ymax = max - x;
        
        long l = binarySearch(vec, ymin, min, max, GEQ);
        long h = binarySearch(vec, ymax, min, max, LEQ);
        
        for (long n = l; n <= h; n++) {
            long y = vec[n];
            long t = x + y;
            if (x == y) {
                continue;
            }
            rset.insert(t);
        }
    }
    std::cout << rset.size() << std::endl;
}

int main(int argc, const char * argv[]) {
// 427
    std::string filename("/Users/rohit/Documents/Development/practice/2Sum/algo1-programming_prob-2sum.txt");
    long min = -10000, max = 10000;
// 8
//    std::string filename("/Users/rohit/Documents/Development/practice/2Sum/small1.txt");
//    long min = 3, max = 10;
// 2
//    std::string filename("/Users/rohit/Documents/Development/practice/2Sum/small2.txt");
//    long min = 0, max = 4;
// 2
//    std::string filename("/Users/rohit/Documents/Development/practice/2Sum/input_random_1_10.txt");
//    long min = -10000, max = 10000;
// 14
//    std::string filename("/Users/rohit/Documents/Development/practice/2Sum/input_random_19_160.txt");
//    long min = -10000, max = 10000;
// 55
//    std::string filename("/Users/rohit/Documents/Development/practice/2Sum/input_random_30_1280.txt");
//    long min = -10000, max = 10000;

    LongVec vec;
    loadData(filename, vec);
//    compute2Sum(vec, min, max);
    computeFast2Sum(vec, min, max);

    return 0;
}
