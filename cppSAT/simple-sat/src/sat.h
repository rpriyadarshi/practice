/*
 * Ref: https://sahandsaba.com/understanding-sat-by-implementing-a-simple-sat-solver-in-python.html
 * C++ Author: Rohit Priyadarshi
 * Date: 02/08/2021
*/

#pragma once

/*
 * Solves SAT instance by reading from stdin using an iterative or recursive
 * watchlist-based backtracking algorithm. Iterative algorithm is used by default,
 * unless the --recursive flag is given. Empty lines and lines starting with a #
 * will be ignored.
 */
class SATManager {
public: // Aliases
    using Assignment = std::vector<int>;

private: // Data

public: // Constructors/destructors
    SATManager() {}
    ~SATManager() {}

public: // Core
};
