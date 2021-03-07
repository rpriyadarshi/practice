//
// Created by rohit on 3/6/21.
//

#include <iostream>
#include <vector>

#include "rackoner.h"
#include "schema.h"
#include "generator.h"

Generator::Generator(int items, int width) {

}

Generator::~Generator() {

}

void Generator::print() const {

}

void Generator::solve(int prefix, int width, int suffix) {
    Rackoner r(suffix, width);
    Schema s0(0, width, suffix, r.getSpan());
//    r.print();
    s0.print();
    _count = 1;
    while (r.next()) {
        Schema s(prefix, width, suffix, r.getSpan());
//        r.print();
        s.print();
        _count++;
    }
}
