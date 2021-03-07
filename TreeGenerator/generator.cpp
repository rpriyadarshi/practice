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
    while (r.next()) {
        Schema s(prefix, width, suffix, r.getSpan());
        s.print();
        _count++;
    }
}

void Generator::solve() {
    Rackoner r(_items, 0);
    Schema s(_items, 0, 0, r.getSpan());
    s.print();
    for (int i = 1; i < _items; i++) {
        int prefix = _items - i;
        int suffix = i;
        int width = std::min(_width, suffix);
        solve(prefix, width, suffix);
    }
}
