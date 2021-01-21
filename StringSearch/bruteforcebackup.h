//
// Created by rohit on 1/19/21.
//

#pragma once

class BruteForceBackup : public Search {
public: // Constructors/destructors
    BruteForceBackup(const std::string_view& pat) : Search(pat) {
    }

public: // Core
    int multisearch(const std::string& txt, int start) const {
        int n = txt.size();
        int i, j;
        for (i = start, j = 0; i < n && j < _m; i++) {
            if (txt[i] == _pat[j]) {
                j++;
            } else {
                i -= j;
                j = 0;
            }
        }
        if (j == _m) {
            return i - _m;
        }
        return -1;
    }
};

class SolutionBFBK : public Solution {
public:
    bool multisearch(const std::string_view& pat, const std::string& txt) {
        BruteForceBackup bf(pat);
        bf.search(txt);
        bool found = bf.validate(txt, _idxes);
//        bf.print();
        return found;
    }
};
