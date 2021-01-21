//
// Created by rohit on 1/20/21.
//

#pragma once

class KnuthMorrisPratt : public Search {
public: // Aliases
    using Dfa = std::vector<std::vector<int>>;

private: // Data
    int _base{128};                 // Base you are operating on
    Dfa _dfa;                       // DFA built from pattern

public: // Constructors/destructors
    KnuthMorrisPratt(const std::string_view& pat) : Search(pat) {
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
    int multisearch(const std::string& txt, int start) const {
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
