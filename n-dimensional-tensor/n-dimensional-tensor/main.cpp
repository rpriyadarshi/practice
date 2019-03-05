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
// 5-Tensor
void testOne() {
    std::cout << __FUNCTION__ << std::endl;
    nten::UIntVec evec;
    evec.push_back(3);
    evec.push_back(4);
    evec.push_back(5);
    evec.push_back(3);
    evec.push_back(1);
    unsigned int size = 3*4*5*3*1;

    float* data = new float[size];
    std::memset(data, 0.0, size*sizeof(float));

    nten::tensor<nten::runfunc> ten(data, evec);
    ten.enableDebug();
    std::cout << "Running index-tree --" << std::endl;
    ten.calculateMean();
}

////////////////////////////////////////////////////////////////////////////////
// 3D matrix
void testTwo() {
    std::cout << __FUNCTION__ << std::endl;
    nten::UIntVec evec;
    evec.push_back(4);
    evec.push_back(3);
    evec.push_back(5);

    float data[] = {
        1, 2, 3, 2,
        2, 3, 4, 3,
        1, 2, 3, 2,
        
        2, 3, 4, 3,
        3, 4, 5, 4,
        2, 3, 4, 3,

        3, 4, 5, 4,
        4, 5, 6, 5,
        5, 4, 5, 4,
        
        2, 3, 4, 3,
        3, 4, 5, 4,
        2, 3, 4, 3,

        1, 2, 3, 2,
        2, 3, 4, 3,
        1, 2, 3, 2
    };

    nten::tensor<nten::runfunc> ten(data, evec);
    ten.enableDebug();
    std::cout << "Running index-tree --" << std::endl;
    ten.calculateMean();
}

////////////////////////////////////////////////////////////////////////////////
// Simple 2D matrix
void testThree() {
    std::cout << __FUNCTION__ << std::endl;
    nten::UIntVec evec;
    evec.push_back(4);
    evec.push_back(3);

    float data[] = {
        1, 2, 3, 2,
        2, 3, 4, 3,
        1, 2, 3, 2
    };
    
    nten::tensor<nten::runfunc> ten(data, evec);
    ten.enableDebug();
    std::cout << "Running index-tree --" << std::endl;
    float* mean = ten.calculateMean();
    std::cout << "Dumping mean tensor --" << std::endl;
    unsigned int sz = sizeof(data) / sizeof(float);
    for (int i = 0; i < sz; i++) {
        std::cout << mean[i] << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    testOne();
    testTwo();
    testThree();

    return 0;
}
