//
// Created by rohit on 3/5/21.
//

#include <iostream>
#include <vector>
#include <cassert>

#include "rackoner.h"

Rackoner::Rackoner(const int width, const int items): _span(width), _items(items) {
    _span[0] = _items;
}

Rackoner::~Rackoner() {

}

bool Rackoner::moveOnce() {
    bool moved = false;
    int i = 0;
    for (int j = 1; j < _span.size(); j++) {
        if (_span[j] == 0) {
            _span[0] = _items - j;
            for (int k = 1; k <= j; k++) {
                _span[k] = 1;
            }
            moved = true;
            break;
        }
        if (_span[i] - _span[j] > 1) {
            _span[i]--;
            _span[j]++;
            moved = true;
            break;
        }
        i = j;
    }
    return moved;
}

void Rackoner::print() const {
    for (auto& s : _span) {
        std::cout << s << " ";
    }
    std::cout << std::endl;
}

