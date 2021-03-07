//
// Created by rohit on 3/6/21.
//

#pragma once

// Prefix is lowest node where branching happens
// Width is the current branching factor
// Suffix is nodes in the branches
class Schema {
public: // Aliases
    using IntVec = std::vector<int>;

private: // Data
    int _prefix{0};
    int _width{0};
    int _suffix{0};
    IntVec _branches;

public: // Constructors/destructors
    Schema(int prefix, int width, int suffix, const IntVec& branches);
    ~Schema();

public: // Accessors
    [[nodiscard]] int getPrefix() const { return _prefix; }
    [[nodiscard]] int getWidth() const { return _width; }
    [[nodiscard]] int getSuffix() const { return _suffix; }
    [[nodiscard]] const IntVec& getBranches() const { return _branches; }

private: // Accessors
    void setPrefix(int prefix) { _prefix = prefix; }
    void setWidth(int width) { _width = width; }
    void setSuffix(int suffix) { _suffix = suffix; }

public: // Helpers
    static void printHeader();
    void print() const;

public: // Core
};