//
//  main.cpp
//  FactorialSum
//
//  Created by Rohit Priyadarshi on 2/21/13.
//  Copyright (c) 2013 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>

unsigned long long factorial(int n)
{
    unsigned long long v = 1;
    for (unsigned long i = 1; i <= n; i++) {
        v *= i;
    }
    return v;
}

unsigned long long sum(int n)
{
    unsigned long long v = 0;
    for (int i = 1; i <= n; i++) {
        v += factorial(i);
    }
    return v;
}

int main(int argc, const char * argv[])
{
    std::cout << sum(20) << std::endl;
    return 0;
}

