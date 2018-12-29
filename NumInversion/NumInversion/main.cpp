//
//  main.cpp
//  NumInversion
//
//  Created by Rohit Priyadarshi on 5/20/18.
//  Copyright © 2018 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>

typedef std::vector<int> IntVec;

size_t mergeAndCountSplitInv(const IntVec& cv, const IntVec& dv, IntVec& b) {
    int i = 0;
    int j = 0;
    size_t splitInv = 0;
    size_t n = cv.size() + dv.size();
    for (int k = 0; k < n; k++) {
        int c = cv[i];
        int d = dv[j];
        if (i >= cv.size()) {
            c = std::numeric_limits<int>::max();
        }
        if (j >= dv.size()) {
            d = std::numeric_limits<int>::max();
        }
        if (c < d) {
            b.push_back(c);
            i++;
        } else {
            b.push_back(d);
            j++;
            splitInv = splitInv + (n/2 - i);
        }
    }
    return splitInv;
}

size_t sortAndCountInv(const IntVec& a, IntVec& b) {
    size_t len = a.size();
    size_t cntInv;
    if (len == 0 || len == 1) {
        b = a;
        cntInv = 0;
    } else {
        const IntVec la(a.begin(), a.begin() + len / 2);
        const IntVec ra(a.begin() + len / 2, a.end());

        IntVec c, d;
        size_t leftInv = sortAndCountInv(la, c);
        size_t rightInv = sortAndCountInv(ra, d);
        size_t splitInv = mergeAndCountSplitInv(c, d, b);
        cntInv = leftInv + rightInv + splitInv;
    }

    return cntInv;
}

void loadData(const std::string& filename, IntVec& vec) {
    std::ifstream istrm(filename);
    if (!istrm.is_open()) {
        std::cout << "failed to open " << filename << '\n';
    } else {
        int v;
        while (istrm >> v) {
            vec.push_back(v);
        }
    }
}

int main(int argc, const char * argv[]) {
    //IntVec vec {1, 3, 5, 2, 4, 6};
    IntVec vec;
    loadData("/Users/rohit/Documents/Development/practice/NumInversion/IntegerArray.txt", vec);
    for (auto data : vec) {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    IntVec r;
    for (auto data : r) {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    size_t cnt = sortAndCountInv(vec, r);
    std::cout << cnt << std::endl;
    return 0;
}
