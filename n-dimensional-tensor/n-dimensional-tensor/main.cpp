//
//  main.cpp
//  n-dimensional-tensor
//
//  Created by Rohit Priyadarshi on 3/3/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <vector>

#include "tensor.hpp"

int main(int argc, const char * argv[]) {
    nten::ExtentVec evec;
    evec.push_back(3);
    evec.push_back(4);
    evec.push_back(5);
    evec.push_back(3);
    evec.push_back(1);
    
    nten::IndexVec idx;
    idx.resize(evec.size(), 0);
    float* data = nullptr;
    
    nten::tensor ten(data, evec);
    ten.indexTree(idx);

    return 0;
}
