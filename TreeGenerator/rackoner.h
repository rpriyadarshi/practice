//
// Created by rohit on 3/5/21.
//

#pragma once

class Rackoner {
public: // Aliases
    using IntVec = std::vector<int>;

private: // Data
    IntVec _span;
    int _items{0};

public: // Constructors/destructors
    Rackoner(const int width, const int items);
    ~Rackoner();

public: // Accessors
public: // Helpers
    void print() const;
public: // Core
    bool moveOnce();
};