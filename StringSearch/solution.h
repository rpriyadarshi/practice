//
// Created by rohit on 1/19/21.
//

#pragma once

class Solution {
public: // Aliases
    using Idxes = std::vector<size_t>;

protected: // Data
    Idxes _idxes;

public:
    virtual bool multisearch(const std::string_view& pat, const std::string& txt) = 0;
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
            found = multisearch(pat, s);
        }
        return found;
    }
};