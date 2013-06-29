//
//  main.cpp
//  Beal
//
//  Created by Rohit Priyadarshi on 6/8/13.
//  Copyright (c) 2013 Rohit Priyadarshi. All rights reserved.
//

#include "beal_impl.h"

int main(int argc, const char * argv[])
{
    Beal::Cache<size_t> beal(25, 10);
    //Beal::Cache<size_t> beal(10, 15);
    //Beal::Cache<unsigned long> beal(100, 10);
    //Beal::Cache<unsigned long> beal(100, 9);
    beal.sort();
    //std::cout << beal;
    // 3^3 + 6^3 = 3^5
    // 7^6 + 7^7 = 98^3
    size_t a = 3, x = 3, b = 6, y = 3, c, z;
    beal.calculate(a, x, b, y, c, z);
    beal.print(std::cout, a, x, b, y, c, z);
    a = 7; x = 6; b = 7; y = 7;
    beal.calculate(a, x, b, y, c, z);
    beal.print(std::cout, a, x, b, y, c, z);
    
    beal.search();
    return 0;
}

