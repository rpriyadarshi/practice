//
//  main.cpp
//  Beal
//
//  Created by Rohit Priyadarshi on 6/8/13.
//  Copyright (c) 2013 Rohit Priyadarshi. All rights reserved.
//

#include "beal.h"

int main(int argc, const char * argv[])
{
    Beal::Cache b(25, 10);
    //Beal::Cache b(10, 15);
    //Beal::Cache b(100, 9);
    b.sort();
    std::cout << b;
    // 3^3 + 6^3 = 3^5
    // 7^6 + 7^7 = 98^3
    b.calculate(3, 3, 6, 3);
    b.calculate(7, 6, 7, 7);
    return 0;
}

