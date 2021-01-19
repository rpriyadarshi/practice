#include <iostream>
#include <vector>
#include <map>
#include <string>

// Adapted from Algorithms, 4th edition, Sedgewick
// Algorithm 5.8
// Prime numbers
//  < 1000: 997
//  12 bit: 2557
//  16 bit: 61051
//  32 bit: 2210774273
//  64 bit: 5467909550323529693
class RabinKarp {
public: // Aliases
    using HashData = std::tuple<long, int>;
    using IntVec = std::vector<int>;
    using HashVec = std::vector<HashData>;
    using HashIdxes = std::map<long, IntVec>;

private: // Data
    long _phash;                    // Pattern hash value
    int _m;                         // Pattern length
    long _prime{997};               // Your choice of a prime number (e.g. 997)
    int _base{256};                 // Base you are operating on
    long _coeff{1};                 // Coefficient, base^(m - 1) % prime to remove leading digit
    const std::string_view& _pat;   // Needed for Las Vages verification

public: // Data
    mutable IntVec _matches;        // Store all matches
    mutable HashVec _hashes;        // Hashes at each end index
    mutable HashIdxes _hashIdxes;

public: // Constructors/destructors
    RabinKarp(const std::string_view& pat) : _pat(pat) {
        _m = _pat.size();
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
        // int j = 0;
        // for (int i = pos; i < pos + _m; i++) {
        //     char t = txt[i];
        //     char p = _pat[j++];
        //     if (p != t) {
        //         return false;
        //     }
        // }
        // return true;
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
        _hashIdxes[thash].emplace_back(0);
        for (int i = _m; i < n; i++) {
            // Remove leading digit
            thash = (thash + _prime - (_coeff * txt[i - _m]) % _prime) % _prime;
            // Add trailing digit
            thash = (thash * _base + txt[i]) % _prime;
            _hashes.emplace_back(thash, i - _m + 1);
            _hashIdxes[thash].emplace_back(i - _m + 1);;
        }
    }
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
        std::cout << "  key [" << _pat << "] hits [";
        for (int i = 0; i < _matches.size() - 1; i++) {
            std::cout << _matches[i] << " ";
        }
        std::cout << _matches[_matches.size() - 1];
        std::cout << "]" << std::endl;
        std::cout << "    hashes [";
        for (int i = 0; i < _hashes.size() - 1; i++) {
            std::cout << std::get<0>(_hashes[i]) << " [" << std::get<1>(_hashes[i]) << "] ";
        }
        std::cout << std::get<0>(_hashes[_hashes.size() - 1]) << " [" << std::get<1>(_hashes[_hashes.size() - 1]) << "] ";
        std::cout << "]" << std::endl;
        std::cout << "    sets   [";
        for (auto hf : _hashIdxes) {
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

class Solution {
public:
    std::string encode(std::string s) {
        for (size_t i = 4; i < s.size() / 2 + 1; i++) {
            std::string_view sv{s.data() + 0, i};
            RabinKarp rk(sv);
            rk.search(s);
            rk.hashes(s);
            rk.print();
        }

        return s;
    }
};

void runtest(const std::string& s) {
    std::cout << "Solving \"" << s << "\" ..." << std::endl;
    Solution sol;
    sol.encode(s);
}

int main() {
    runtest("aaa");
    runtest("aaaaa");
    runtest("aaaaaaaaaa");
    runtest("aabcaabcd");
    runtest("abbbabbbcabbbabbbc");

    return 0;
}
