/*
 * Ref: https://sahandsaba.com/understanding-sat-by-implementing-a-simple-sat-solver-in-python.html
 * C++ Author: Rohit Priyadarshi
 * Date: 02/07/2021
*/

#pragma once

class SATSolver {
public: // Aliases
    using Assignment = std::vector<int>;

private: // Data
    const SATInstance& _instance;
    const Monitor _monitor;

public: // Constructors/destructors
    SATSolver(const SATInstance& instance, const Monitor& monitor) : _instance(instance), _monitor(monitor) {}
    ~SATSolver() {}

public: // Core
};

