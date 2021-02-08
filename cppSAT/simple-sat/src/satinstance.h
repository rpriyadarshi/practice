/*
 * Some notes on encoding:
 * - Variables are encoded as numbers 0 to n - 1.
 * - Literal v is encoded as 2 * v and ~v as 2 * v + 1. So the foremost
 *         bit of a literal encodes whether it is negated or not. This can be
 *         tested simply with checking if l & 1 is 0 or 1.
 * - To negate a literal, we just have to toggle the foremost bit. This
 *         can done easily by an XOR with 1: the negation of l is l ^ 1.
 * - To get a literal's variable, we just need to shift to the right. This
 * can be done with l >> 1.
 *
 * Example: Let's say variable b is encoded with number 3. Then literal b
 * is encoded as 2 * 3 = 6 and ~b as  2 * 3 + 1 = 7.
 *
 * Ref: https://sahandsaba.com/understanding-sat-by-implementing-a-simple-sat-solver-in-python.html
 * C++ Author: Rohit Priyadarshi
 * Date: 02/07/2021
 */

#pragma once

class SATInstance {
public: // Aliases
    using Variables = std::vector<std::string>;
    using VariableTable = std::unordered_map<std::string, int>;
    using Clause = std::vector<int>;
    using Clauses = std::vector<Clause>;
    using Assignment = std::vector<int>;

private: // Data
    Variables _variables;
    VariableTable _variable_table;
    Clauses _clauses;

public: // Constructors/destructors
    SATInstance() {}
    ~SATInstance() {}

public: // Accessors
    const Variables& variables() const { return _variables; }
    const VariableTable& variable_table() const { return _variable_table; }
    const Clauses& clauses() const { return _clauses; }

public: // Core
    void parse_and_add_clause(const std::string& line) {
        Clause clause;
        std::istringstream istr(line);
        std::string literal;
        while (istr >> literal) {
            bool negated = literal[0] == '~' ? true : false;
            std::string variable = literal.substr(negated, literal.size());
            auto iter = _variable_table.find(variable);
            if (iter == _variable_table.end()) {
                _variable_table[variable] = _variables.size();
                _variables.emplace_back(variable);
            }
            int encoded_literal = _variable_table[variable] << 1 | negated;
            clause.emplace_back(encoded_literal);
        }
        _clauses.emplace_back(clause);
    }
    void from_file(const std::string& file) {
        std::ifstream ifstr(file.c_str());
        std::string line;
        while (std::getline(ifstr, line)) {
            std::istringstream istr(line);
            std::string comment;
            istr >> comment;
            if (! comment.empty() && comment[0] != '#') {
                parse_and_add_clause(line);
            }
        }

    }
    std::string literal_to_string(int literal) const {
        return ((literal & 1) ? "~" : "") + _variables[literal >> 1];
    }
    std::string clause_to_string(const Clause& clause) const {
        std::string ret;
        for (int i = 0; i < clause.size(); i++) {
            auto& l = clause[i];
            if (i > 0) {
                ret += " ";
            }
            ret += std::move(literal_to_string(l));
        }
        return ret;
    }
    std::string assignment_to_string(const Assignment& assignment, bool brief = false, const std::string& starting_with = "") const {

        return "";
    }
    void print() const {
        std::cout << "Variables -" << std::endl;
        for (auto& var : _variables) {
            std::cout << var << " ";
        }
        std::cout << std::endl;

        std::cout << "Variable Table -" << std::endl;
        for (auto& var : _variable_table) {
            std::cout << "[" << var.first << ":" << var.second << "] ";
        }
        std::cout << std::endl;

        std::cout << "Clauses -" << std::endl;
        for (auto& cl : _clauses) {
            std::cout << "[";
            std::cout << clause_to_string(cl);
            std::cout << "]" << std::endl;
        }
    }
};