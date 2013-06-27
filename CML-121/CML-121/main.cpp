//
//  main.cpp
//  CML-121
//
//  Created by Rohit Priyadarshi on 1/24/13.
//  Copyright (c) 2013 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>

int calculate(int a, int b)
{
    int p = 2*a + b;
    int q = 2*a - b;
    return q != 0 ? p/q : 0;
}

int main(int argc, const char * argv[])
{
    int max = 0;
    for (int a = 1; a <= 100; a++) {
        for (int b = 1; b <= 100; b++) {
            int val = calculate(a, b);
            max = val > max ? val : max;
        }
    }
    std::cout << "Max value is: " << max << std::endl;
    return 0;
}

