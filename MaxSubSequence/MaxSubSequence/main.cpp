//
//  main.cpp
//  MaxSubSequence
//
//  Created by Rohit Priyadarshi on 6/12/11.
//  Copyright 2011 VirtualSamaj. All rights reserved.
//

#include <iostream>

template <class T>
T Max(T t1, T t2) {
    return t1 > t2 ? t1 : t2;
}

int MaxSubSum(const int a[], int left, int right)
{
    if (left == right) {
        if (a[left] > 0) {
            return a[left];
        }
        else
        {
            return 0;
        }
    }
    
    int center = (left + right)/2;
    int maxLeftSum = MaxSubSum(a, left, center);
    int maxRightSum = MaxSubSum(a, center + 1, right);
    
    int maxLeftBorderSum = 0;
    int leftBorderSum = 0;
    for (int i = center; i >= left; --i) {
        leftBorderSum += a[i];
        if (leftBorderSum > maxLeftBorderSum)
        {
            maxLeftBorderSum = leftBorderSum;
        }
    }
    int maxRightBorderSum = 0;
    int rightBorderSum = 0;
    for (int i = center + 1; i <= right; ++i) {
        rightBorderSum += a[i];
        if (rightBorderSum > maxRightBorderSum)
        {
            maxRightBorderSum = rightBorderSum;
        }
    }
    return Max<int>(Max<int>(maxLeftSum, maxRightSum), 
                    maxLeftBorderSum + maxRightBorderSum);
}

int MaxSubdequenceSum1(const int a[], int n)
{
    int maxSum = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            int thisSum = 0;
            for (int k = i; k <= j; ++k)
            {
                thisSum += a[k];
            }
            
            if (thisSum > maxSum)
            {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}

int MaxSubdequenceSum2(const int a[], int n)
{
    int maxSum = 0;
    for (int i = 0; i < n; ++i) {
        int thisSum = 0;
        for (int j = i; j < n; ++j) {
            thisSum += a[j];
            
            if (thisSum > maxSum) {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}

int MaxSubdequenceSum3(const int a[], int n)
{
    return MaxSubSum(a, 0, n-1);
}

int MaxSubdequenceSum4(const int a[], int n)
{
    int thisSum = 0;
    int maxSum = 0;
    for (int j = 0; j < n; ++j) {
        thisSum += a[j];
        
        if (thisSum > maxSum) {
            maxSum = thisSum;
        }
        else {
            if (thisSum < 0) {
                thisSum = 0;
            }
        }
    }
    return maxSum;
}

int main (int argc, const char * argv[])
{
    int a[] = {4, -3, 5, -2, -1, 2, 6, -2};
    int n = sizeof(a)/sizeof(int);
    
    int s1 = MaxSubdequenceSum1(a, n);
    int s2 = MaxSubdequenceSum2(a, n);
    int s3 = MaxSubdequenceSum3(a, n);
    int s4 = MaxSubdequenceSum4(a, n);
    
    std::cout << s1 << std::endl << s2 << std::endl<< s3 << std::endl << s4 << std::endl;
    return 0;
}

