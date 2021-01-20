//
// Created by rohit on 1/19/21.
//

class Solution459 {
public: // Aliases
    using Freq = std::array<int, 26>;
    using UsedFreq = std::vector<int>;

protected: // Data
    Freq _freq;
    UsedFreq _usedFreq;

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
    bool repeatedSubstringPattern(std::string s) {
        _freq.fill(0);

        // Frequency of alphabets
        for (int i = 0; i < s.size(); i++) {
            int idx = s[i] - 'a';
            _freq[idx]++;
        }

        // Find min-max range
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

        // A loner implies that there is no repeats
        if (minf == 1) {
            return false;
        }

        int grps = std::gcd(minf, maxf);
        for (auto f : _usedFreq) {
            grps = std::gcd(f, grps);
        }
        int patsize = s.size() / grps;

        // No pattern was found
        if (grps == 1) {
            return false;
        }

        std::cout << "groups [" << grps << "] patsize [" << patsize << "]" << std::endl;

        // Check if all used alphabets are multiples of same frequency
        for (auto f : _usedFreq) {
            if (f % grps != 0) {
                return false;
            }
        }

        // Extract pattern
        std::string_view pat(s.data(), patsize);

        // Match the pattern on the entire string
        for (int i = patsize; i < s.size(); i += patsize) {
            for (int j = 0; j < patsize; j++) {
                if (s[i + j] != pat[j]) {
                    return false;
                }
            }
        }

        return true;
    }
};