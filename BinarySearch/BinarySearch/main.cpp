//
//  main.cpp
//  BinarySearch
//
//  Created by Rohit Priyadarshi on 6/14/11.
//  Copyright 2011 VirtualSamaj. All rights reserved.
//

#include <iostream>
#include <vector>

size_t BinarySearch(const std::vector<int>& v, int x)
{
    size_t low = 0;
    size_t high = v.size()-1;
    while (low <= high) {
        size_t mid = (high+low)/2;
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
    size_t a = BinarySearch(v, 5);
    size_t b = BinarySearch(v, 97);
    size_t c = BinarySearch(v, 25);
    size_t d = BinarySearch(v, 55);
    size_t e = BinarySearch(v, 75);
    size_t f = BinarySearch(v, 15);
    
    std::cout << a << b << c << d << e << f << std::endl;
    return 0;
}

