//
//  main.cpp
//  RodCutting
//
//  Created by Rohit Priyadarshi on 9/24/11.
//  Copyright 2011 VirtualSamaj. All rights reserved.
//

#include <iostream>

int bottom_up_rod_cut(int p[], int n)
{
    int r[n+1];
    r[0] = 0;
    for (int j = 0; j < n; ++j) {
        int q = INT_MIN;
        for (int i = 0; i <= j; ++i) {
            q = std::max(q, p[i] + r[j - i]);
        }
        r[j+1] = q;
    }
    return r[n];
}

int memoized_rod_cut_aux(int p[], int n, int r[])
{
    if (r[n] >= 0) {
        return r[n];
    }
    int q;
    if (n == 0) {
        q = 0;
    }
    else
    {
        q = INT_MIN;
        for (int i = 0; i < n; ++i) {
            q = std::max(q, p[i] + memoized_rod_cut_aux(p, n - i - 1, r));
        }
    }
    r[n] = q;
    return q;
}

int memoized_rod_cut(int p[], int n)
{
    int r[n+1];
    for (int i = 0; i <= n; ++i) {
        r[i] = INT_MIN;
    }
    return memoized_rod_cut_aux(p, n, r);
}

int cut_rod(int p[], int n)
{
    if (n == 0)
    {
        return 0;
    }
    int q = INT_MIN;
    for (int i = 0; i < n; ++i) {
        q = std::max(q, p[i] + cut_rod(p, n - i - 1));
    }
    return q;
}

int main (int argc, const char * argv[])
{
    int p[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n = 5; //sizeof(p)/sizeof(int);
    std::cout << "Rod-cut=" << cut_rod(p, n) << std::endl;
    std::cout << "Memoized-Rod-cut=" << memoized_rod_cut(p, n) << std::endl;
    std::cout << "Bottom-Up-Rod-cut=" << bottom_up_rod_cut(p, n) << std::endl;
    return 0;
}

