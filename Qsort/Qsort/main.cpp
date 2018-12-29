//
//  main.cpp
//  Qsort
//
//  Created by Rohit Priyadarshi on 5/27/18.
//  Copyright © 2018 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>

typedef std::vector<int> IntVec;

void swap(IntVec& a, int i, int j) {
    int t = a[j];
    a[j] = a[i];
    a[i] = t;
}

void printVec(IntVec& a, int l, int r) {
    for (int i = l; i <= r; i ++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

void checkSort(IntVec& a, int l, int r) {
    int unsorted = 0;
    int p = a[l];
    for (int i = l + 1; i <= r; i++) {
        int q = a[i];
        unsorted += (p > q);
        p = q;
    }
    if (unsorted) {
        std::cout << "Unsorted elements found!" << std::endl;
    } else {
        std::cout << "All sorted!" << std::endl;
    }
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

int chooseLeft(IntVec& a, int l, int r) {
    return l;
}

int chooseRight(IntVec& a, int l, int r) {
    return r;
}

int chooseMedian(IntVec& a, int l, int r) {
    int k = l + (r - l)/2;
    int p = a[l];
    int q = a[r];
    int m = a[k];
    
    int i = 0;
    
    if (p < q) {
        if (p < m) {
            if (q < m) { // q
                i = r;
            } else if (q > m) { // m
                i = k;
            } else { // q == m
                i = k;
            }
        } else if (p > m) { // p
            i = l;
        } else { // p == m
            i = l;
        }
    } else if (p > q) {
        if (p < m) { // p
            i = l;
        } else if (p > m) {
            if (q < m) { // m
                i = k;
            } else if (q > m) { // q
                i = r;
            } else { // q == m
                i = r;
            }
        } else { // p == m
            i = l;
        }
    } else { // p == q
        i = l;
    }
    
//    printVec(a, 0, a.size() - 1);
//    std::cout << i << ": " << l << " " << k << " " << r << std::endl;
//    std::cout << a[i] << ": " << p << " " << m << " " << q << std::endl;
//    std::cout << std::endl;
    return i;
}

int choosePivot(IntVec& a, int l, int r) {
//    return chooseLeft(a, l, r); // 162085
//    return chooseRight(a, l, r); // 164123
    return chooseMedian(a, l, r); // 138382
}

int partition(IntVec& a, int l, int r) {
    int p = a[l];
    int i = l + 1;
    for (int j = l + 1; j <= r; j++) {
        int q = a[j];
        if (q < p) {
            swap(a, j, i);
            i++;
        }
    }
    swap(a, l, i - 1);
    return i - 1;
}

int quickSort(IntVec& a, int l, int r) {
    if (l >= r) {
        return 0;
    } else {
        int i = choosePivot(a, l, r);
        swap(a, l, i);
        int j = partition(a, l, r);
        int c = r - l;
        c += quickSort(a, l, j - 1);
        c += quickSort(a, j + 1, r);
        return c;
    }
}

int main(int argc, const char * argv[]) {
//    IntVec a {10, 2, 13, 8, 16, 11, 5, 3, 12, 6, 14, 1, 7, 4, 15, 9};
//    IntVec a {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//    IntVec a {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
//    IntVec a {4, 5, 6, 7};

    IntVec a;
    loadData("/Users/rohit/Documents/Development/practice/Qsort/QuickSort.txt", a);
    
    int l = 0;
    int r = a.size() - 1;
//    int r = 9;
    
    int c = quickSort(a, l, r);
    
//    printVec(a, l, r);
    checkSort(a, l, r);
    std::cout << "Comparisons -- actual: " << c << std::endl;
    std::cout << "estimated: " << (r - l) * std::log2(r - l) << " - " << (r - l)*(r - l) << std::endl;
    return 0;
}
