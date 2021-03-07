//
// Created by rohit on 3/6/21.
//

#include <iostream>
#include <vector>

#include "rackoner.h"
#include "schema.h"
#include "generator.h"

Generator::Generator(int items, int width) : _items(items), _width(width) {

}

Generator::~Generator() {

}

void Generator::print() const {

}

void Generator::solve(int prefix, int width, int suffix) {
    Rackoner r(suffix, width);
//    Schema s0(prefix, _width, suffix, r.getSpan());
//    r.print();
//    s0.print();
    while (r.next()) {
        Schema s(prefix, width, suffix, r.getSpan());
//        r.print();
        s.print();
        _count++;
    }
}

void Generator::solve() {
    _count++; // For the first chain
    for (int i = 1; i < _items; i++) {
        int prefix = _items - i;
        int suffix = i;
        int width = std::min(_width, suffix);
        solve(prefix, width, suffix);
    }
}
