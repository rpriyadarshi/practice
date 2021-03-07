//
// Created by rohit on 3/5/21.
//

#include <iostream>
#include <vector>
#include <cassert>

#include "rackoner.h"

Rackoner::Rackoner(int items, int width): _items(items), _span(width) {
    _span[0] = _items;
}

Rackoner::~Rackoner() {

}

bool Rackoner::moveOnce() {
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
}

bool Rackoner::next() {
    bool moved = false;
    for (int j = 1; j < _span.size() && !moved; j++) {
        moved |= next(j);
    }
    return moved;
}

bool Rackoner::next(int idx) {
    _j = idx;
    bool moved = false;
    int i = _j - 1;
    if (_span[_j] == 0) { // New column
        _span[0] = _items - _j;
        for (int k = 1; k <= _j; k++) {
            _span[k] = 1;
        }
        moved = true;
    } else if (_span[i] - _span[_j] > 1) {// previous borrow
        _span[i]--;
        _span[_j]++;
        moved = true;
    } else { // More borrow
        while (i >= 0) {
            if (_span[i] - _span[_j] > 1) {
                _span[i]--;
                _span[_j]++;
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

