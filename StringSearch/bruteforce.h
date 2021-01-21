//
// Created by rohit on 1/19/21.
//

#pragma once

class BruteForce : public Search {
public: // Constructors/destructors
    BruteForce(const std::string_view& pat) : Search(pat) {
    }

public: // Core
    int multisearch(const std::string& txt, int start) const {
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
};

class SolutionBF : public Solution {
public:
    bool multisearch(const std::string_view& pat, const std::string& txt) {
        BruteForce bf(pat);
        bf.search(txt);
        bool found = bf.validate(txt, _idxes);
//        bf.print();
        return found;
    }
};
