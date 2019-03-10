//
//  common.cpp
//  graphs
//
//  Created by Rohit Priyadarshi on 3/10/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include "common.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace adt {

void dumpVal(std::ostream& o, int val) {
    if (val < NegInfLimit) {
        o << "-\u221E";
    } else if (val > PosInfLimit) {
        o << "+\u221E";
    } else {
        o << val;
    }
}

};

