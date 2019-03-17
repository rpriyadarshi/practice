//
//  common.cpp
//  graphs
//
//  Created by Rohit Priyadarshi on 3/10/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <fstream>
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

// http://www.cplusplus.com/forum/general/108679/
std::istream& ignoreline(std::ifstream& ifstr, std::ifstream::pos_type& pos) {
    pos = ifstr.tellg();
    return ifstr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string getlastline(std::ifstream& ifstr) {
    std::ifstream::pos_type pos = ifstr.tellg();

    std::ifstream::pos_type lastPos;
    while (ifstr >> std::ws && ignoreline(ifstr, lastPos)) {
        pos = lastPos;
    }
    
    ifstr.clear();
    ifstr.seekg(pos);

    std::string line;
    std::getline(ifstr, line);
    return line;
}

};

