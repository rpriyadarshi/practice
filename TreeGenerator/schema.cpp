//
// Created by rohit on 3/6/21.
//

#include <iostream>
#include <vector>

#include "schema.h"

Schema::Schema(int prefix, int width, int suffix, const IntVec& branches) : _prefix(prefix), _width(width), _suffix(suffix), _branches(branches) {

}

Schema::~Schema() {

}

void Schema::print() const {
    std::cout << "SCHEMA {";
    std::cout << "prefix(" << _prefix << "), ";
    std::cout << "width(" <<  _width << "), ";
    std::cout << "suffix(" <<  _suffix << "), ";

    std::cout << "branches[";
    for (int i = 0; i < _branches.size(); i++) {
        if (i) {
            std::cout << " ";
        }
        std::cout << _branches[i];
    }
    std::cout << "]";
    std::cout << "}";
    std::cout << std::endl;

}
