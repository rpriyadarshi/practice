//
// Created by rohit on 3/5/21.
//

#include <iostream>
#include <vector>
#include <cassert>

#include "rackoner.h"

Rackoner::Rackoner(int width, int items): _span(width), _items(items) {
    _span[0] = _items;
}

Rackoner::~Rackoner() {

}

bool Rackoner::moveOnce() {
#if 0
    bool moved = false;
    int i = 0;
    for (int j = 1; j < _span.size() && !moved; j++) {
        if (_span[j] == 0) { // New column
            _span[0] = _items - j;
            for (int k = 1; k <= j; k++) {
                _span[k] = 1;
            }
            moved = true;
        } else if (_span[i] - _span[j] > 1) { // previous borrow
            _span[i]--;
            _span[j]++;
            moved = true;
        } else { // More borrow
            while (i >= 0) {
                if (_span[i] - _span[j] > 1) {
                    _span[i]--;
                    _span[j]++;
                    moved = true;
                }
                i--;
            }
        }
        i = j;
    }
    return moved;
#else
    bool moved = false;
    for (int j = 1; j < _span.size() && !moved; j++) {
        moved |= moveOnce(j);
    }
    return moved;
#endif
}

bool Rackoner::moveOnce(int j) {
    bool moved = false;
    int i = j - 1;
    if (_span[j] == 0) { // New column
        _span[0] = _items - j;
        for (int k = 1; k <= j; k++) {
            _span[k] = 1;
        }
        moved = true;
    } else if (_span[i] - _span[j] > 1) {// previous borrow
        _span[i]--;
        _span[j]++;
        moved = true;
    } else { // More borrow
        while (i >= 0) {
            if (_span[i] - _span[j] > 1) {
                _span[i]--;
                _span[j]++;
                moved = true;
            }
            i--;
        }
    }
    return moved;
}

void Rackoner::print() const {
    for (auto& s : _span) {
        std::cout << s << " ";
    }
    std::cout << std::endl;
}

