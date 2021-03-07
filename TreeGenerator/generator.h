//
// Created by rohit on 3/6/21.
//

#pragma once

class Generator {
public: // Aliases
    using IntVec = std::vector<int>;

private: // Data
    int _items{0};
    int _width{0};
    int _count{1};

public: // Constructors/destructors
    Generator(int items, int width);
    ~Generator();

public: // Accessors
    [[nodiscard]] int getItems() const { return _items; }
    [[nodiscard]] int getWidth() const { return _width; }
    [[nodiscard]] int getCount() const { return _count; }

private: // Accessors
    void setItems(int items) { _items = items; }
    void setWidth(int width) { _width = width; }
    void setCount(int count) { _count = count; }

public: // Helpers
    void print() const;

public: // Core
    void solve(int prefix, int width, int suffix);
    void solve();
};

