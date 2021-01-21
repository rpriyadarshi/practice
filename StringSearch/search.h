//
// Created by rohit on 1/20/21.
//

#pragma once

class Search {
public: // Aliases
    using Matches = std::vector<int>;
    using Idxes = std::vector<size_t>;

protected: // Data
    int _m;                         // Pattern length
    const std::string_view &_pat;   // Needed for Las Vages verification

protected: // Data
    mutable Matches _matches;        // Store all matches

public: // Constructors/destructors
    Search(const std::string_view& pat) : _pat(pat), _m(pat.size()) {
    }

public: // Core
    virtual int multisearch(const std::string& txt, int start) const = 0;
    virtual void search(const std::string& txt) const {
        for (int i = 0; i < txt.size(); i += _m) {
            int idx = multisearch(txt, i);
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
