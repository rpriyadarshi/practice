/*
 * Ref: https://sahandsaba.com/understanding-sat-by-implementing-a-simple-sat-solver-in-python.html
 * C++ Author: Rohit Priyadarshi
 * Date: 02/07/2021
*/

#pragma once

/*
 * Recursively solve SAT by assigning to variables d, d+1, ..., n-1. Assumes
 * variables 0, ..., d-1 are assigned so far. A generator for all the
 * satisfying assignments is returned.
 */
class RSATSolver : public SATSolver {
public: // Aliases
    using Assignment = std::vector<int>;

private: // Data

public: // Constructors/destructors
    RSATSolver(const SATInstance& instance, const Monitor& monitor) : SATSolver(instance, monitor) {}
    ~RSATSolver() {}

public: // Core
};
