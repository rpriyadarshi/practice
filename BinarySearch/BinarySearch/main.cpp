//
//  main.cpp
//  BinarySearch
//
//  Created by Rohit Priyadarshi on 6/14/11.
//  Copyright 2011 VirtualSamaj. All rights reserved.
//

#include <iostream>
#include <vector>

int BinarySearch(const std::vector<int>& v, int x)
{
    int low = 0;
    int high = v.size()-1;
    while (low <= high) {
        int mid = (high+low)/2;
        if (v[mid] < x) {
            low = mid+1;
        }
        else
        {
            if (v[mid] > x) {
                high = mid-1;
            }
            else
            {
                return mid;
            }
        }
    }
    return 0;
}

int main (int argc, const char * argv[])
{
    std::vector<int> v;
    for (int i = 0; i < 100; ++i) {
        v.push_back(i);
    }
    int a = BinarySearch(v, 5);
    int b = BinarySearch(v, 97);
    int c = BinarySearch(v, 25);
    int d = BinarySearch(v, 55);
    int e = BinarySearch(v, 75);
    int f = BinarySearch(v, 15);
    
    std::cout << a << b << c << d << e << f << std::endl;
    return 0;
}

