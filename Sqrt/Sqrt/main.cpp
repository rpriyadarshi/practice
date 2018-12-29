//
//  main.cpp
//  Sqrt
//
//  Created by Rohit Priyadarshi on 11/19/18.
//  Copyright © 2018 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>

short isqrt(short num) {
    short res = 0;
    short bit = 1 << 14; // The second-to-top bit is set: 1 << 30 for 32 bits
    
    // "bit" starts at the highest power of four <= the argument.
    while (bit > num)
        bit >>= 2;
    
    while (bit != 0) {
        if (num >= res + bit) {
            num -= res + bit;
            res += bit << 1;
        }
        
        res >>= 1;
        bit >>= 2;
    }
    return res;
}

int main(int argc, const char * argv[]) {
    std::cout << isqrt() << std::endl;
    return 0;
}
