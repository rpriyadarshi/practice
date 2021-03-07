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
    Rackoner(int items, int width);
    ~Rackoner();

public: // Accessors
    [[nodiscard]] const IntVec& getSpan() const { return _span; }
    [[nodiscard]] int getItems() const { return _items; }

private: // Accessors
    void setItems(int items) { _items = items; }

public: // Helpers
    void print() const;

public: // Core
    bool moveOnce();
    bool next();
    bool next(int idx);
};