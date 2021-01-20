//
// Created by rohit on 1/19/21.
//

#pragma once

class BruteForce {
public: // Aliases
    using Matches = std::vector<int>;
    using Idxes = std::vector<size_t>;

private: // Data
    int _m;                         // Pattern length
    const std::string_view &_pat;   // Needed for Las Vages verification

public: // Data
    mutable Matches _matches;        // Store all matches

public: // Constructors/destructors
    BruteForce(const std::string_view& pat) : _pat(pat), _m(pat.size()) {
    }

public: // Core
    int search(const std::string& txt, int start) const {
        int n = txt.size();
        for (int i = start; i <= n - _m; i++) {
            int j;
            for (j = 0; j < _m; j++) {
                if (txt[i + j] != _pat[j]) {
                    break;
                }
            }
            if (j == _m) {
                return i;
            }
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

class SolutionBF {
public: // Aliases
    using Idxes = std::vector<size_t>;

private: // Data
    Idxes _idxes;

public:
    bool search(const std::string_view& pat, const std::string& txt) {
        BruteForce bf(pat);
        bf.search(txt);
        bool found = bf.validate(txt, _idxes);
//        bf.print();
        return found;
    }

    bool search(const std::string& s) {
        if (s.size() <= 1) {
            return false;
        }
        bool same = true;
        // Repeat of first char
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == s[0]) {
                _idxes.push_back(i);
            }
            if (s[i] != s[i - 1]) {
                same = false;
            }
        }
        if (same) {
            return same;
        }
        bool found = false;
        for (int i = 0; i < std::min(_idxes.size() / 2 + 1, _idxes.size()) && !found; i++) {
            std::string_view pat{s.data() + 0, _idxes[i]};
            found = search(pat, s);
        }
        return found;
    }
};
