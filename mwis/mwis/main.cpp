//
//  main.cpp
//  mwis
//
//  Created by Rohit Priyadarshi on 1/1/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <fstream>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
class Vertex;

////////////////////////////////////////////////////////////////////////////////
typedef std::vector<Vertex*> VertexVec;
typedef std::vector<unsigned long> WeightVec;
typedef std::vector<unsigned long> IndexVec;

////////////////////////////////////////////////////////////////////////////////
// Edge class maintains both vertices
class Vertex {
public:
    Vertex() : m_id(0), m_weight(0) {}
    Vertex(unsigned long id, unsigned long weight) : m_id(id), m_weight(weight) {}
    ~Vertex() {}
    
public: // Accessors
    unsigned long getId() const { return m_id; }
    unsigned long getWeight() const { return m_weight; }
    
public: // Accessors
    unsigned long getId() { return m_id; }
    unsigned long getWeight() { return m_weight; }
    
private:
    unsigned long m_id;
    unsigned long m_weight;
};

////////////////////////////////////////////////////////////////////////////////
class MwIs {
public:
    MwIs() {}
    ~MwIs() {}
    
public:
    bool readSize(std::ifstream& ifstr);
    bool readEdge(std::ifstream& ifstr);
    bool read(const std::string& filename);

public:
    void compute();
    void retrace();

public:
    void dumpVertex(std::ostream& o, Vertex* v);
    void dumpCalc(std::ostream& o, unsigned long w);
    void dumpVertices(std::ostream& o);
    void dumpCalcs(std::ostream& o);
    void dumpResults(std::ostream& o);
    void dumpIdxs(std::ostream& o, IndexVec& idxs);
    void dump(std::ostream& o);

public:
    int m_items;
    VertexVec m_cache;
    WeightVec m_calc;
    VertexVec m_result;
};

////////////////////////////////////////////////////////////////////////////////
inline bool MwIs::readSize(std::ifstream& ifstr) {
    std::string line;
    std::getline(ifstr, line);
    if (! ifstr.good()) {
        return false;
    }
    std::stringstream istr(line);
    istr >> m_items;
    return true;
}

inline bool MwIs::readEdge(std::ifstream& ifstr) {
    std::string line;
    std::getline(ifstr, line);
    if (! ifstr.good()) {
        return false;
    }
    std::stringstream istr(line);
    unsigned long weight;
    istr >> weight;
    
    Vertex* n = new Vertex(m_cache.size() + 1, weight);
    m_cache.push_back(n);
    
    return true;
}

inline bool MwIs::read(const std::string& filename) {
    std::ifstream ifstr(filename);
    if (! ifstr.good()) {
        std::cout << "ERROR: Could not read \"" << filename << "\"" << std::endl;
        return false;
    }
    // Get graph size
    if (! readSize(ifstr)) {
        return false;
    }
    
    while (readEdge(ifstr));
    return false;
}

// A[i] = max{A[i - 1], A[i - 2] + wi]}
inline void MwIs::compute() {
    m_calc.clear();
    m_calc.resize(m_items);
    m_calc[0] = m_cache[0]->getWeight();
    m_calc[1] = m_cache[1]->getWeight();
    for (int i = 2; i < m_cache.size(); i++) {
        unsigned long w = m_cache[i]->getWeight();
        unsigned long w1 = m_calc[i - 1];
        unsigned long w2 = m_calc[i - 2];
        unsigned long wx = std::max(w1, w2 + w);

        m_calc[i] = wx;
    }
}

inline void MwIs::retrace() {
    int i = static_cast<int>(m_calc.size()) - 1;
    while (i >= 0) {
        unsigned long w = m_cache[i]->getWeight();
        unsigned long w1 = m_calc[i - 1];
        unsigned long w2 = m_calc[i - 2];

        if (w1 > w2 + w) {
//            m_result.push_back(m_cache[i]);
            i -= 1;
        } else {
            m_result.push_back(m_cache[i]);
            i -= 2;
        }
    }
}

inline void MwIs::dumpVertex(std::ostream& o, Vertex* v) {
    if (! v) return;
    o << v->getId() << "[" << v->getWeight() << "]";
}

inline void MwIs::dumpCalc(std::ostream& o, unsigned long w) {
    o << "[" << w << "]";
}

inline void MwIs::dumpVertices(std::ostream& o) {
    for (auto& v : m_cache) {
        dumpVertex(o, v);
        o << std::endl;
    }
}

inline void MwIs::dumpCalcs(std::ostream& o) {
    for (auto& w : m_calc) {
        dumpCalc(o, w);
        o << std::endl;
    }
}

inline void MwIs::dumpResults(std::ostream& o) {
    for (auto& v : m_result) {
        dumpVertex(o, v);
        o << std::endl;
    }
}

inline void MwIs::dumpIdxs(std::ostream& o, IndexVec& idxs) {
    for (auto& id : idxs) {
        for (auto& v : m_result) {
            if (v->getId() == id) {
                dumpVertex(o, v);
                o << std::endl;
            }
        }
    }
    for (auto& id : idxs) {
        bool rc = false;
        for (auto& v : m_result) {
            if (v->getId() == id) {
                rc = true;
                break;
            }
        }
        o << rc;
    }
    o << std::endl;
}

inline void MwIs::dump(std::ostream& o) {
    dumpVertices(o);
    o << std::endl;
    dumpCalcs(o);
    o << std::endl;
    dumpResults(o);
    o << std::endl;
}

int main(int argc, const char * argv[]) {
//    1[4962786]
//    3[5601590]
//    117[7463231]
//    517[5906419]
//    10100110
    std::string filename("/Users/rohit/Documents/Development/practice/mwis/mwis.txt");
// Max sum: 2616, chosen points (position): [2, 4, 6, 8, 10]
//    std::string filename("/Users/rohit/Documents/Development/practice/mwis/mwis2.txt");
// Max sum: 2533, chosen points (position): [1, 3, 6, 9]
//    std::string filename("/Users/rohit/Documents/Development/practice/mwis/mwis3.txt");
    IndexVec idxs {1, 2, 3, 4, 17, 117, 517, 997};

    MwIs mwis;
    mwis.read(filename);
    mwis.compute();
    mwis.retrace();
    mwis.dump(std::cout);
    mwis.dumpIdxs(std::cout, idxs);
    return 0;
}
