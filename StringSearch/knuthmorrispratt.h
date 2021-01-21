//
// Created by rohit on 1/20/21.
//

#pragma once

class KnuthMorrisPratt {
public: // Aliases
    using Matches = std::vector<int>;
    using Idxes = std::vector<size_t>;
    using Dfa = std::vector<std::vector<int>>;

private: // Data
    int _m;                         // Pattern length
    int _base{256};                 // Base you are operating on
    const std::string_view &_pat;   // Needed for Las Vages verification
    Dfa _dfa;                       // DFA built from pattern

public: // Data
    mutable Matches _matches;        // Store all matches

public: // Constructors/destructors
    KnuthMorrisPratt(const std::string_view& pat) : _pat(pat), _m(pat.size()) {
        builddfa();
    }

public: // Core
    void builddfa() {
        _dfa.resize(_base);
        for (int i = 0; i < _base; i++) {
            _dfa[i].resize(_m);
        }
        _dfa[_pat[0]][0] = 1;
        for (int x = 0, j = 1; j < _m; j++) {
            for (int c = 0; c < _base; c++) {
                _dfa[c][j] = _dfa[c][x];    // Copy mismatch cases
            }
            _dfa[_pat[j]][j] = j + 1;       // Setup match case
            x = _dfa[_pat[j]][x];
        }
    }
    int search(const std::string& txt, int start) const {
        int n = txt.size();
        int i, j;
        for (i = start, j = 0; i < n && j < _m; i++) {
            j = _dfa[txt[i]][j];
        }
        if (j == _m) {
            return i - _m;
        }
        return -1;
    }
    void search(const std::string& txt) const {
        for (int i = 0; i < txt.size(); i += _m) {
            int idx = search(txt, i);
            if (idx > 0) {
                _matches.push_back(idx);
            }
        }
    }
    bool validate(const std::string& txt, const Idxes& idxes) const {
        if (_matches.empty()) {
            return false;
        }
        for (int i = 1; i < _matches.size(); i++) {
            if (_matches[i - 1] + _pat.size() != _matches[i]) {
                return false;
            }
        }
        int estSize = _pat.size() + _matches[_matches.size() - 1];
        return txt.size() == estSize;
    }

    void print() const {
        std::cout << "  key [" << _pat << "]" << std::endl;
        printMatches();
    }
    void printMatches() const {
        if (_matches.empty()) {
            return;
        }
        std::cout << "    matches [";
        for (int i = 0; i < _matches.size() - 1; i++) {
            std::cout << _matches[i] << " ";
        }
        std::cout << _matches[_matches.size() - 1];
        std::cout << "]" << std::endl;
    }
};

class SolutionKMP : public Solution {
public:
    bool multisearch(const std::string_view& pat, const std::string& txt) {
        KnuthMorrisPratt bf(pat);
        bf.search(txt);
        bool found = bf.validate(txt, _idxes);
//        bf.print();
        return found;
    }
};
