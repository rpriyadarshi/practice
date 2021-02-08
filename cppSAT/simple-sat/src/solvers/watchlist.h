/*
 * Ref: https://sahandsaba.com/understanding-sat-by-implementing-a-simple-sat-solver-in-python.html
 * C++ Author: Rohit Priyadarshi
 * Date: 02/07/2021
*/

#pragma once

class Monitor {
public: // Aliases
    using Variables = std::vector<std::string>;
    using VariableTable = std::unordered_map<std::string, int>;
    using Clause = std::vector<int>;
    using Watchdeque = std::deque<Clause>;
    using Watchlist = std::vector<Watchdeque>;
    using Assignment = std::vector<int>;

private: // Data
    const SATInstance& _instance;
    Watchlist _watchlist;

public: // Constructors/destructors
    Monitor(const SATInstance& instance) : _instance(instance) {
        setup_watchlist();
    }
    ~Monitor() {}

public: // Core
    void dump_watchlist() const {
        std::cout << "Current watchlist:" << std::endl;
        for (int l = 0; l < _watchlist.size(); l++) {
            auto& cl = _watchlist[l];
            std::string literal_string = std::move(_instance.literal_to_string(l));
            std::string clauses_string;
            for (int i = 0; i < cl.size(); i++) {
                if (i > 0) {
                    clauses_string += ", ";
                }
                clauses_string += _instance.clause_to_string(cl[i]);
            }
            std::cout << literal_string << ": " << clauses_string << std::endl;
        }
    }
    void setup_watchlist() {
        _watchlist.resize(2 * _instance.variables().size());
        for (auto& cl : _instance.clauses()) {
            _watchlist[cl[0]].emplace_back(cl);
        }
    }
    /*
    * Updates the watch list after literal 'false_literal' was just assigned
    * False, by making any clause watching false_literal watch something else.
    * Returns False it is impossible to do so, meaning a clause is contradicted
    * by the current assignment.
    */
    bool update_watchlist(int false_literal, const Assignment& assignment, bool verbose) {
        while (!_watchlist[false_literal].empty()) {
            auto& clause = _watchlist[false_literal][0];
            bool found_alternative = false;
            for (auto& alternative : clause) {
                int v = alternative >> 1;
                int a = alternative & 1;
                if (assignment[v] < 0 || assignment[v] == a ^ 1) {
                    found_alternative = true;
                    _watchlist[false_literal][0].clear();
                    _watchlist[alternative].emplace_back(clause);
                    break;
                }
            }
            if (!found_alternative) {
                if (verbose) {
                    dump_watchlist();
                    std::cout << "Current assignment: " << _instance.assignment_to_string(assignment) << std::endl;
                    std::cout << "Clause " << _instance.clause_to_string(clause) << "contradicted." << std::endl;
                }
                return false;
            }
        }
        return true;
    }
};