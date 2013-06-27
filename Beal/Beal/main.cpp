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
    Beal::Cache c(25, 10);
    //Beal::Cache c(10, 15);
    //Beal::Cache c(100, 9);
    c.sort();
    std::cout << c;
    return 0;
}

