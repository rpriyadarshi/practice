//
//  main.cpp
//  Median
//
//  Created by Rohit Priyadarshi on 7/14/18.
//  Copyright © 2018 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

typedef std::vector<int> IntVec;
typedef std::priority_queue<int, IntVec, std::greater<int>> IntMinPQueue;
typedef std::priority_queue<int, IntVec, std::less<int>> IntMaxPQueue;

class Median {
public: // Constructor/destructor
    Median() {}
    ~Median() {}
    
public:
    int insert(int v);
    
public:
    IntMinPQueue m_hHigh;
    IntMaxPQueue m_hLow;
};

inline int Median::insert(int v) {
    if (m_hLow.empty()) {
        m_hLow.push(v);
    } else {
        if (v < m_hLow.top()) {
            m_hLow.push(v);
        } else {
            m_hHigh.push(v);
        }
    }
    if (m_hLow.size() > m_hHigh.size() + 1) {
        int l = m_hLow.top();
        m_hLow.pop();
        m_hHigh.push(l);
    } else if (m_hLow.size() + 1 < m_hHigh.size()) {
        int h = m_hHigh.top();
        m_hHigh.pop();
        m_hLow.push(h);
    }
    if (m_hLow.size() > m_hHigh.size()) {
        return m_hLow.top();
    } else if (m_hLow.size() < m_hHigh.size()) {
        return m_hHigh.top();
    } else {
        return m_hLow.top();
    }
}

void loadData(const std::string& filename, IntVec& vec) {
    std::ifstream istrm(filename);
    if (!istrm.is_open()) {
        std::cout << "failed to open " << filename << '\n';
    } else {
        int v;
        while (istrm >> v) {
            vec.push_back(v);
        }
    }
}

int main(int argc, const char * argv[]) {
    IntVec vec;
    std::string filename("/Users/rohit/Documents/Development/practice/Median/Median.txt");
//    std::string filename("/Users/rohit/Documents/Development/practice/Median/MedianSmall.txt");
    loadData(filename, vec);
    
    Median m;
    int sum = 0;
    for (auto v: vec) {
        int s = m.insert(v);
        sum += s;
//        std::cout << s << std::endl;
    }
    std::cout
        << "(" << m.m_hLow.size()
        << ":" << m.m_hLow.top()
        << ") - (" << m.m_hHigh.size()
        << ":" << m.m_hHigh.top()
        << ")" << std::endl;
    std::cout << sum << std::endl;
    std::cout << sum%10000 << std::endl;

    return 0;
}
