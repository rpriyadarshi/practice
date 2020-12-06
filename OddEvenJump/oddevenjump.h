class Solution {
public: // Aliases
    using IntVec = std::vector<int>;
    using IntSet = std::set<int>;
    using IntSetMap = std::map<int, IntSet>;
    using IntPair = std::pair<int, int>;
    using IntPairStack = std::stack<IntPair>;
        
private: // Data
    IntSetMap _cache;
    IntVec _up;
    IntVec _dn;
    IntVec _preup;
    IntVec _predn;

public:
    void buildCache(const IntVec& A) {
        for (int i = 0; i < A.size(); i++) {
            auto val = A[i];
            auto& data = _cache[val];
            data.insert(i);
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

    bool oddEvenJump(const IntVec& A, int start) {
        IntPairStack stack;
        int oddCycle{-1};
        int i = start;
        int j = start;
        int res = -1;
        while (res < 0 && i >= 0 && i < A.size() - 1) {
            if (oddCycle < 0) {
                res = _preup[i];
                j = _up[i];
//                std::cout << "[odd " << " -> (" << i << ", " << j << ")]";
            } else {
                res = _predn[i];
                j = _dn[i];
//                std::cout << "[even" << " -> (" << i << ", " << j << ")]";
            }
            stack.emplace(IntPair(oddCycle, i));
            i = j;
            oddCycle *= -1;
        }
        if (res < 0) {
            res = (i == A.size() - 1);
            while (! stack.empty()) {
                auto& data = stack.top();
                if (data.first < 0) {
                    _preup[data.second] = res;
                } else {
                    _predn[data.second] = res;
                }
                stack.pop();
            }
        }
//        std::cout << " -> {" << rc << "}" << std::endl;
        return res;
    }

    void printPre(const IntVec& A) {
        std::cout << "[";
        for (int i = 0; i < A.size(); i++) {
            std::cout << _preup[i] << " ";
        }
        std::cout << "]" << std::endl;
        std::cout << "[";
        for (int i = 0; i < A.size(); i++) {
            std::cout << _predn[i] << " ";
        }
        std::cout << "]" << std::endl;
    }

    int oddEvenJumps(std::vector<int>& A) {
        buildCache(A);
//         printCache(A);
        buildUpDn(A);
//         printUpDn(A);

        _cache.clear();

        _preup.resize(A.size(), -1);
        _predn.resize(A.size(), -1);

        int cycles = 0;
        for (int start = 0; start < A.size(); start++) {
            cycles += oddEvenJump(A, start);
        }
//        printPre();
        return cycles;
    }
};
