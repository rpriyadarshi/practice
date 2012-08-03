//
//  main.cpp
//  Euclid
//
//  Created by Rohit Priyadarshi on 6/15/11.
//  Copyright 2011 VirtualSamaj. All rights reserved.
//

#include <iostream>

unsigned int
Gcd(unsigned int m, unsigned int n)
{
    unsigned int rem;
    while (n > 0) {
        rem = m%n;
        m = n;
        n = rem;
    }
    
    return m;
}

int main (int argc, const char * argv[])
{

    // insert code here...
    std::cout << Gcd(27, 3) << std::endl;
    std::cout << Gcd(105, 5) << std::endl;
    std::cout << Gcd(36, 18) << std::endl;
    std::cout << Gcd(110, 20) << std::endl;
    std::cout << Gcd(121, 11) << std::endl;
    std::cout << Gcd(119, 27) << std::endl;
    std::cout << Gcd(100, 50) << std::endl;
    return 0;
}

