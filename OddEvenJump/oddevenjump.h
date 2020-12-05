class Solution {
public: // Aliases
    using IntVec = std::vector<int>;
    using IntList = std::list<int>;
    using IntListMap = std::map<int, IntList>;
        
private: // Data
    IntListMap _cache;
    IntVec _up;
    IntVec _dn;

public:
    void buildCache(const IntVec& A) {
        for (int i = 0; i < A.size(); i++) {
            auto val = A[i];
            auto& data = _cache[val];
            data.push_back(i);
        }
    }
    void printCache(const IntVec& A) const {
        for(auto& elem : _cache) {
            auto& key = elem.first;
            auto& data = elem.second;
            std::cout << key << " -> [";
            for (auto& d : data) {
                std::cout << d << ", ";
            }
            std::cout << "]" << std::endl;
        }
    }

    int findUp(const IntVec& A, int idx) const {
        int val = A[idx];
        int found = -1;
        auto iter = _cache.find(val);
        for (; iter != _cache.end() && found < 0; iter++) {
            auto& data = iter->second;
            for (auto& d : data) {
                if (d > idx || d == A.size() - 1) {
                    found = d;
                    break;
                }
            }
        }
        return found;
    }

    int findDn(const IntVec& A, int idx) const {
        int val = A[idx];
        int found = -1;
        auto iter = _cache.find(val);
        for (; iter != _cache.begin() && found < 0; iter--) {
            auto& data = iter->second;
            for (auto& d : data) {
                if (d > idx || d == A.size() - 1) {
                    found = d;
                    break;
                }
            }
        }
        if (found < 0 && iter == _cache.begin()) {
            auto& data = iter->second;
            for (auto& d : data) {
                if (d > idx || d == A.size() - 1) {
                    found = d;
                    break;
                }
            }
        }
        return found;
    }
    
    void buildUpDn(const IntVec& A) {
        _up.resize(A.size());
        _dn.resize(A.size());

        for (int i = 0; i < A.size() - 1; i++) {
            auto up = findUp(A, i);
            auto dn = findDn(A, i);
            _up[i] = (up);
            _dn[i] = (dn);
        }
        _up[A.size() - 1] = (A.size() - 1);
        _dn[A.size() - 1] = (A.size() - 1);
    }
    void printUpDn(const IntVec& A) const {
        for (int i = 0; i < A.size(); i++) {
            std::cout << "A[" << i << "]=" << A[i] 
                << " -> [" << _up[i] << "]["<< _dn[i] << "]["
                << std::endl;
        }
    }
    
    bool oddEvenJump2(const IntVec& A, int start) const {
        int oddCycle{-1};
        int i = start; 
        while (i >= 0 && i < A.size() - 1) {
            if (oddCycle < 0) {
                i = _up[i];
            } else {
                i = _dn[i];
            }
            
            oddCycle *= -1;
        }
        return i == A.size() - 1;
    }
    int solve2(const IntVec& A) {
        buildCache(A);
        // printCache(A);
        buildUpDn(A);
        // printUpDn(A);

        _cache.clear();
        
        int cycles[A.size()];
        for (int i = 0; i < A.size(); i++) {
            cycles[i] = oddEvenJump2(A, i);
        }
        
        int count = 0;
        for (int i = 0; i < A.size(); i++) {
            count += cycles[i];
        }
        return count;

    }


    int findBestOdd(const IntVec& A, int start) const {
        int best = -1;
        int i = start + 1;
        for (; i < A.size(); i++) {
            if ((A[start] <= A[i]) && (best < 0 || A[best] > A[i])) {
                best = i;
            }
        }
        return best;
    }
    int findBestEven(const IntVec& A, int start) const {
        int best = -1;
        int i = start + 1;
        for (; i < A.size(); i++) {
            if ((A[start] >= A[i]) && (best < 0 || A[best] < A[i])) {
                best = i;
            }
        }
        return best;
    }
    bool oddEvenJump1(const IntVec& A, int start) const {
        int oddCycle{-1};
        int i = start; 
        while (i >= 0 && i < A.size() - 1) {
            if (oddCycle < 0) {
                i = findBestOdd(A, i);
            } else {
                i = findBestEven(A, i);
            }
            
            oddCycle *= -1;
        }
        return i == A.size() - 1;
    }
    int solve1(const IntVec& A) const {
        int cycles[A.size()];
        for (int i = 0; i < A.size(); i++) {
            cycles[i] = oddEvenJump1(A, i);
        }
        
        int count = 0;
        for (int i = 0; i < A.size(); i++) {
            count += cycles[i];
        }
        return count;
    }
    
    int oddEvenJumps(std::vector<int>& A) {
        int cycles = 0;
        if (A.size() < 0) {
            cycles = solve1(A);
        } else {
            cycles = solve2(A);
        }
        return cycles;
    }
};
