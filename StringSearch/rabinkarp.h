//
// Created by rohit on 1/19/21.
//

#pragma once

// Adapted from Algorithms, 4th edition, Sedgewick
// Algorithm 5.8
// Prime numbers
//  < 1000: 997
//  12 bit: 2557
//  16 bit: 61051
//  32 bit: 2210774273
//  64 bit: 5467909550323529693
class RabinKarp : public Search {
public: // Aliases
    using HashData = std::tuple<long, int>;
    using Matches = std::vector<int>;
    using Hashes = std::vector<HashData>;
    using Groups = std::map<long, Matches>;

private: // Data
    long _phash;                    // Pattern hash value
    long _prime{2210774273};        // Your choice of a prime number (e.g. 997)
    int _base{256};                 // Base you are operating on
    long _coeff{1};                 // Coefficient, base^(m - 1) % prime to remove leading digit

public: // Data
    mutable Hashes _hashes;          // Hashes at each end index
    mutable Groups _groups;

public: // Constructors/destructors
    RabinKarp(const std::string_view& pat) : Search(pat) {
        for (int i = 1; i <= _m - 1; i++) {
            _coeff = (_base * _coeff) % _prime;
        }
        _phash = hash(pat);
    }

public: // Core
    bool check(const std::string& txt, int pos) const {
        // Monte Carlo
        return true;
        // Las Vegas to verify pattern
//         int j = 0;
//         for (int i = pos; i < pos + _m; i++) {
//             char t = txt[i];
//             char p = _pat[j++];
//             if (p != t) {
//                 return false;
//             }
//         }
//         return true;
    }

    long hash(const std::string_view& key) const {
        long h = 0;
        for (int i = 0; i < _m; i++) {
            h = (_base * h + key[i]) % _prime;
        }
        return h;
    }
    void hashes(const std::string& txt) const {
        int n = txt.size();
        long thash = hash(txt); // first m characters
        _hashes.emplace_back(thash, (0));
        _groups[thash].emplace_back(0);
        for (int i = _m; i < n; i++) {
            // Remove leading digit
            thash = (thash + _prime - (_coeff * txt[i - _m]) % _prime) % _prime;
            // Add trailing digit
            thash = (thash * _base + txt[i]) % _prime;
            _hashes.emplace_back(thash, i - _m + 1);
            _groups[thash].emplace_back(i - _m + 1);;
        }
    }
    int multisearch(const std::string& txt, int start) const { return -1; };
    void search(const std::string& txt) const {
        int n = txt.size();
        long thash = hash(txt); // first m characters
        if (_phash == thash) {  // Match at the beginning
            _matches.push_back(0);
        }
        for (int i = _m; i < n; i++) {
            // Remove leading digit
            thash = (thash + _prime - (_coeff * txt[i - _m]) % _prime) % _prime;
            // Add trailing digit
            thash = (thash * _base + txt[i]) % _prime;
            // Check for a match
            if (_phash == thash) {
                if (check(txt, i - _m + 1)) {
                    _matches.push_back(i - _m + 1);
                }
            }
        }
    }

    void print() const {
        Search::print();
        printHashes();
        printGroups();
    }
    void printHashes() const {
        if (_hashes.empty()) {
            return;
        }
        std::cout << "    hashes  [";
        for (int i = 0; i < _hashes.size() - 1; i++) {
            std::cout << std::get<0>(_hashes[i]) << " [" << std::get<1>(_hashes[i]) << "] ";
        }
        std::cout << std::get<0>(_hashes[_hashes.size() - 1]) << " [" << std::get<1>(_hashes[_hashes.size() - 1])
                  << "] ";
        std::cout << "]" << std::endl;
    }
    void printGroups() const {
        if (_groups.empty()) {
            return;
        }
        std::cout << "    groups  [";
        for (auto hf : _groups) {
            std::cout << hf.first << " " << hf.second.size() << " [";
            for (int i = 0; i < hf.second.size() - 1; i++) {
                std::cout << hf.second[i] << " ";
            }
            std::cout << hf.second[hf.second.size() - 1];
            std::cout << "] ";
        }
        std::cout << "]" << std::endl;
    }
};

class SolutionRK : public Solution {
public:
    bool multisearch(const std::string_view& pat, const std::string& txt) {
        RabinKarp rk(pat);
        rk.search(txt);
        bool found = rk.validate(txt, _idxes);
//        rk.hashes(txt);
//        rk.print();
        return found;
    }
};
