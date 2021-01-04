//
//  main.cpp
//  permute
//
//  Created by Rohit Priyadarshi on 11/7/18.
//  Copyright © 2018 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <unordered_set>
#include <set>

class Permute {
private: // Aliases
    using StrSet = std::unordered_set<std::string>;

private: // Data
    std::string m_data;
    StrSet m_perm;
    StrSet m_seen;

public:
    Permute(const std::string& data) : m_data(data) {}
    ~Permute() {}
    
public: // operators
    void operator()() { permute(0, m_data.size() - 1); }
    
public: // Helpers
    void swap(size_t l, size_t r) {
        char c = m_data[l];
        m_data[l] = m_data[r];
        m_data[r] = c;
    }
    void permute(size_t l, size_t r) {
        if (l == r) {
            m_perm.insert(m_data);
        } else {
            for (int i = 0; i <= r; i++) {
                swap(l, i);
                permute(l + 1, r);
                swap(l, i);
            }
        }
    }
    
    void dump(std::ostream& o) {
        for (auto& p : m_perm) {
            o << p << std::endl;
        }
        o << m_perm.size() << std::endl;
    }
};

int main(int argc, const char * argv[]) {
    Permute perm("ABCD");
    perm();
    perm.dump(std::cout);
    
    return 0;
}
