//
//  main.cpp
//  Beal
//
//  Created by Rohit Priyadarshi on 6/8/13.
//  Copyright (c) 2013 Rohit Priyadarshi. All rights reserved.
//

#include "beal.hpp"

int main(int argc, const char * argv[])
{
    //Beal::Cache beal<size_t>(25, 10);
    //Beal::Cache beal<size_t>(10, 15);
    Beal::Cache<unsigned long long> beal(1000, 9);
    beal.sort();
#if 0
    //std::cout << beal;
    // 3^3 + 6^3 = 3^5
    // 7^6 + 7^7 = 98^3
    unsigned long long a = 3, x = 3, b = 6, y = 3, c, z;
    beal.calculate(a, x, b, y, c, z);
    beal.print(std::cout, a, x, b, y, c, z);
    a = 7; x = 6; b = 7; y = 7;
    beal.calculate(a, x, b, y, c, z);
    beal.print(std::cout, a, x, b, y, c, z);
    
    beal.search();
#endif
    return 0;
}

