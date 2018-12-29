//
//  main.cpp
//  KargerMinCut
//
//  Created by Rohit Priyadarshi on 6/6/18.
//  Copyright © 2018 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
#include <random>

class Graph {
public: // typedefs
    typedef std::multiset<int> Rows;
    typedef std::map<int, Rows> Cols;
    typedef std::pair<Rows::iterator, Rows::iterator> RowRange;

public: // constructors/destructors
    Graph() {}
    ~Graph() {}
    
public: // Optimization functions
    void merge(int v1, int v2);
    int bipart();
    int randbipart(const std::string& filename, int count);

public: // Utility functions
    int rand();
    
    bool read(const std::string& filename);
    void dump(std::ostream& o);
    void dump();
    void clear();

private: // Utility functions
    int rand(int idx);
    int rand(int l, int r);
    
private:
    Cols m_head;
};

inline int Graph::rand(int l, int r) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(l, r);
    return dis(gen);
}

inline int Graph::rand() {
    if (m_head.empty()) return 0;
    int loc = rand(0, static_cast<int>(m_head.size() - 1));
    Graph::Cols::iterator it = m_head.begin();
    std::advance(it, loc);
    int val = it->first;
    return val;
}

inline int Graph::rand(int idx) {
    if (m_head.at(idx).empty()) return 0;
    int loc = rand(0, static_cast<int>(m_head.at(idx).size() - 1));
    Graph::Rows::iterator it = m_head.at(idx).begin();
    std::advance(it, loc);
    int val = *it;
    return val;
}

inline bool Graph::read(const std::string& filename) {
    std::ifstream ifstr(filename);
    if (! ifstr.good()) {
        return false;
    }
    std::string val;
    while(std::getline(ifstr, val).good()) {
        std::stringstream strstr(val);
        std::string tok;
        
        strstr >> tok;
        int idx = std::stoi(tok);
        m_head[idx] = Rows();
        
        while (strstr >> tok) {
            int val = std::stoi(tok);
            m_head.at(idx).insert(val);
        }
    }
    return true;
}

inline void Graph::dump(std::ostream& o) {
    for (auto& data : m_head) {
        o << data.first << " : ";
        for(auto& d : data.second) {
            o << d << " ";
        }
        o << std::endl;
    }
}

inline void Graph::dump() {
    dump(std::cout);
}

inline void Graph::clear() {
    m_head.clear();
}

inline void Graph::merge(int v1, int v2) {
    Rows& r1 = m_head[v1];
    Rows& r2 = m_head[v2];
    r1.insert(r2.begin(), r2.end());
    r1.erase(v1);
    r1.erase(v2);

    m_head.erase(v2);
    
    for (auto& d : r1) {
        size_t count = m_head.at(d).erase(v2);
        for (int i = 0; i < count; i++) {
            m_head.at(d).insert(v1);
        }
    }

    // cleanup if empty
    if (m_head.at(v1).empty()) {
        m_head.erase(v1);
    }
}

inline int Graph::bipart() {
    while (m_head.size() > 2) {
        int v1 = rand();
        int v2 = rand(v1);
        merge(v1, v2);
    }
    
    int sz = -1;
    for (auto& row : m_head) {
        if (sz < 0) {
            sz = static_cast<int>(row.second.size());
        }
        assert(sz == row.second.size());
    }
    return sz;
}

inline int Graph::randbipart(const std::string& filename, int count) {
    int sz = std::numeric_limits<int>::max();
    for (int i = 0; i < count; i++) {
        read(filename);
        sz = std::min(bipart(), sz);
        clear();
    }
    return sz;
}

int main(int argc, const char * argv[]) {
    Graph g;
    const std::string filename("/Users/rohit/Documents/Development/practice/KargerMinCut/kargerMinCut.txt");
//    const std::string filename("/Users/rohit/Documents/Development/practice/KargerMinCut/sampleGraph.txt");
    int trials = g.randbipart(filename, 10);
    std::cout << "Best Partition = " << trials << std::endl;
    return 0;
}
