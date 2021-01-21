//
// Created by rohit on 1/19/21.
//

class Solution459 {
public: // Aliases
    using Freq = std::array<int, 26>;
    using UsedFreq = std::vector<int>;
    using Multiples = std::vector<int>;

protected: // Data
    Freq _freq;
    UsedFreq _usedFreq;
    mutable Multiples _mults;

public:
    // This factorize function actually builds multiples instead of factors
    void factorize(int n) const {
        _mults.push_back(n);
        while (n % 2 == 0) {
            if (_mults.front() != n) {
                _mults.push_back(n);
            }
            n = n/2;
        }

        for (int i = 3; i <= std::sqrt(n); i = i + 2) {
            while (n % i == 0) {
                if (_mults.front() != n) {
                    _mults.push_back(n);
                }
                n = n / i;
            }
        }

        if (n > 2) {
            if (_mults.front() != n) {
                _mults.push_back(n);
            }
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

        // We factorize to get all multiples that can divide all frequencies
        // But we gather products instead of factors
        factorize(grps);

        // Work with all multiples
        for (int i = _mults.size() - 1; i >= 0; i--) {
            int m = _mults[i];
            int patsize = s.size() / m;
//            std::cout << "mults [" << m << "] patsize [" << patsize << "]" << std::endl;

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
