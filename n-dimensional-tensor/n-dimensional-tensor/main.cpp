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
    std::cout << __FUNCTION__ << std::endl;
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
    std::cout << "Running index-tree --" << std::endl;
    ten.indexTree(idx);
}

////////////////////////////////////////////////////////////////////////////////
void testTwo() {
    std::cout << __FUNCTION__ << std::endl;
    nten::UIntVec evec;
    evec.push_back(4);
    evec.push_back(3);
    evec.push_back(5);

    nten::UIntVec idx;
    idx.resize(evec.size(), 0);
    float* data = new float[4*3*5];
    
    nten::tensor<nten::runfunc> ten(data, evec);
    std::cout << "Running index-tree --" << std::endl;
    ten.indexTree(idx);

    std::cout << "Running envelop 1 --" << std::endl;
    idx.resize(evec.size(), 0);
    nten::UIntVec envIdx = {2, 1, 3};
    unsigned int cells = ten.envelope(envIdx, idx);
    std::cout << "Cells: " << cells << std::endl;
    
    std::cout << "Running envelop 2 --" << std::endl;
    idx.resize(evec.size(), 0);
    envIdx = {0, 0, 0};
    cells = ten.envelope(envIdx, idx);
    std::cout << "Cells: " << cells << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
void testThree() {
    std::cout << __FUNCTION__ << std::endl;
    nten::UIntVec evec;
    evec.push_back(4);
    evec.push_back(3);

    nten::UIntVec idx;
    idx.resize(evec.size(), 0);
    float* data = new float[4*3];
    
    nten::tensor<nten::runfunc> ten(data, evec);
    std::cout << "Running index-tree --" << std::endl;
    ten.indexTree(idx);
    
    std::cout << "Running envelop 1 --" << std::endl;
    idx.resize(evec.size(), 0);
    nten::UIntVec envIdx = {2, 1};
    unsigned int cells = ten.envelope(envIdx, idx);
    std::cout << "Cells: " << cells << std::endl;
    std::cout << "Running envelop 2 --" << std::endl;
    idx.resize(evec.size(), 0);
    envIdx = {0, 0};
    cells = ten.envelope(envIdx, idx);
    std::cout << "Cells: " << cells << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    testOne();
    testTwo();
    testThree();

    return 0;
}
