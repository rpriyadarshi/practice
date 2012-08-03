//
//  main.cpp
//  Pow
//
//  Created by Rohit Priyadarshi on 6/16/11.
//  Copyright 2011 VirtualSamaj. All rights reserved.
//

bool
isEven(unsigned int n)
{
    return !(n%2);
}

long int
Pow(long int x, unsigned int n)
{
    if (n == 0) {
        return 1;
    }
    
    if (isEven(n)) {
        return Pow(x*x, n/2);
    }
    else
    {
        return Pow(x*x, n/2)*x;
    }
}

#include <iostream>

int main (int argc, const char * argv[])
{
    std::cout << Pow(10, 4) << std::endl;
    std::cout << Pow(10, 5) << std::endl;
    return 0;
}

