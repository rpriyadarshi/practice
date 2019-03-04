//
//  main.cpp
//  n-dimensional-tensor
//
//  Created by Rohit Priyadarshi on 3/3/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <vector>

#include "common.hpp"
#include "tensor.hpp"
#include "runfunc.hpp"

////////////////////////////////////////////////////////////////////////////////
void testOne() {
    nten::UIntVec evec;
    evec.push_back(3);
    evec.push_back(4);
    evec.push_back(5);
    evec.push_back(3);
    evec.push_back(1);
    
    nten::UIntVec idx;
    idx.resize(evec.size(), 0);
    float* data = nullptr;
    
    nten::tensor<nten::runfunc> ten(data, evec);
    ten.indexTree(idx);
}

////////////////////////////////////////////////////////////////////////////////
void testTwo() {
    nten::UIntVec evec;
    evec.push_back(4);
    evec.push_back(3);
    evec.push_back(5);

    nten::UIntVec idx;
    idx.resize(evec.size(), 0);
    float* data = nullptr;
    
    nten::tensor<nten::runfunc> ten(data, evec);
    ten.indexTree(idx);
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    testOne();
    testTwo();

    return 0;
}
