//
// Created by rohit on 1/19/21.
//

class Solution459 {
public: // Aliases
    using Freq = std::array<int, 26>;
    using UsedFreq = std::vector<int>;
    using Factors = std::vector<int>;
    using Groups = std::set<int>;

protected: // Data
    Freq _freq;
    UsedFreq _usedFreq;
    mutable Factors _facts;
    mutable Groups _grps;

public:
    int gcd1(int a, int b) const {
        if (b == 0) {
            return a;
        }
        return gcd1(b, a % b);
    }
    int gcd2(int a, int b) const {
        if (a == 0 || b == 0) {
            return 0;
        } else if (a == b) {
            return a;
        } else if (a > b) {
            return gcd2(a - b, b);
        } else {
            return gcd2(a, b - a);
        }
    }
    void factorize(int n) const {
        while (n % 2 == 0) {
            _facts.push_back(2);
            n = n/2;
        }

        for (int i = 3; i <= std::sqrt(n); i = i + 2) {
            while (n % i == 0) {
                _facts.push_back(i);
                n = n/i;
            }
        }

        if (n > 2) {
            _facts.push_back(n);
        }
    }

    bool repeatedSubstringPattern(std::string s) {
        _freq.fill(0);

        // Gather frequency of alphabets
        for (int i = 0; i < s.size(); i++) {
            int idx = s[i] - 'a';
            _freq[idx]++;
        }

        // Find min-max range for initial gcd
        // Remove all unused alphabets
        int minf = std::numeric_limits<int>::max();
        int maxf = std::numeric_limits<int>::min();
        for (auto f : _freq) {
            if (f <= 0) {
                continue;
            }
            minf = std::min(minf, f);
            maxf = std::max(maxf, f);
            _usedFreq.push_back(f);
        }

        // A loner implies that there were no repeats
        // A single use implies we have no repeats
        if (minf == 1) {
            return false;
        }

        // GCD calculation identifies that there are possible repeats
        // If there is a GCD > 1, for all alphabets then we have a common period
        int grps = std::gcd(minf, maxf);
        for (auto f : _usedFreq) {
            grps = std::gcd(f, grps);
        }

        // No pattern was found
        if (grps == 1) {
            return false;
        }

        // Check if all used alphabets are multiples of same frequency
        for (auto f : _usedFreq) {
            if (f % grps != 0) {
                return false;
            }
        }

        // We factorize to get all multiples that can divide all frequencies
        _grps.insert(grps);
        factorize(grps);
        for (int i = 0; i < _facts.size(); i++) {
            for (int j = i; j < _facts.size(); j++) {
                int mul = _facts[i] * _facts[j];
                if (grps % mul == 0) {
                    _grps.insert(mul);
                }
            }
        }

        for (auto g : _grps) {
            int patsize = s.size() / g;
//            std::cout << "groups [" << g << "] patsize [" << patsize << "]" << std::endl;

            // Extract pattern
            std::string_view pat(s.data(), patsize);

            bool mismatch = false;

            // Match the pattern on the entire string
            for (int i = patsize; i < s.size() && !mismatch; i += patsize) {
                for (int j = 0; j < patsize && !mismatch; j++) {
                    if (s[i + j] != pat[j]) {
                        mismatch = true;
                    }
                }
            }
            if (! mismatch){
                return true;
            }
        }

        return false;
    }
};