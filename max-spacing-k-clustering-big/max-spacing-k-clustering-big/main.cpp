//
//  main.cpp
//  max-spacing-k-clustering-big
//
//  Created by Rohit Priyadarshi on 12/29/18.
//  Copyright © 2018 Rohit Priyadarshi. All rights reserved.
//

//    - Initially, each point in a separate cluster
//    - Repeat until only k clusters:
//      - Let p; q = closest pair of separated points (determines the current spacing)
//      - Merge the clusters containing p & q into a single cluster.
//    Note: Just like Kruskal's MST algorithm, but stopped early.
//    - Points $ vertices, distances $ edge costs, point pairs $ edges.
//    => Called single-link clustering

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <limits>

////////////////////////////////////////////////////////////////////////////////
class UfNode;

////////////////////////////////////////////////////////////////////////////////
typedef std::list<UfNode*> UfNodeList;
typedef std::vector<UfNode*> UfNodeVec;
////////////////////////////////////////////////////////////////////////////////
// General functions
inline unsigned long reverseBits(unsigned long data, size_t width) {
    const unsigned long mask = 1;
    unsigned long rdata = 0;
    for (size_t i = 0; i < width; i++) {
        rdata |= ((data & mask) << (width - i - 1));
        data >>= 1;
    }
    return rdata;
}

inline unsigned long hammingDist(unsigned long d1, unsigned long d2, size_t width) {
    unsigned long dist = 0;
    const unsigned long mask = 1;
    for (size_t i = 0; i < width; i++) {
        dist += ((d1 & mask) ^ (d2 & mask));
        d1 >>= 1;
        d2 >>= 1;
    }
    return dist;
}

inline void dumpBits(std::ostream& o, unsigned long data, size_t width) {
    const unsigned long mask = 1;
    unsigned long rdata = ::reverseBits(data, width);
    for (size_t i = 0; i < width; i++) {
        o << (rdata & mask);
        rdata >>= 1;
    }
}

////////////////////////////////////////////////////////////////////////////////
// class to build Union-Find data-structure
class UfNode {
public:
    explicit UfNode(unsigned long data) : m_data(data), m_parent(this), m_rank(0) {}
    ~UfNode() {}
    
public:
    void incrRank() { m_rank++; }
    UfNode* findParent();
    UfNode* compress();
    void reverseBits(size_t width);
    unsigned long hammingDist(UfNode* n, size_t width);
    
public:
    void dumpBits(std::ostream& o, size_t width);
    
public:
    unsigned long getData() const { return m_data; }
    UfNode* getParent() const { return m_parent; }
    int getRank() const { return m_rank; }
    
public:
    unsigned long getData() { return m_data; }
    UfNode* getParent() { return m_parent; }
    int getRank() { return m_rank; }
    void setParent(UfNode* n) { m_parent = n; }
    
private:
    unsigned long m_data;
    UfNode* m_parent;
    int m_rank;
};

////////////////////////////////////////////////////////////////////////////////
// Implementation
inline UfNode* UfNode::findParent() {
    UfNode* n = this;
    UfNode* p = n->getParent();
    while (n != p) {
        n = p;
        p = p->getParent();
    }
    return p;
}

inline UfNode* UfNode::compress() {
    UfNode* n = this;
    UfNode* p1 = getParent();
    UfNode* p2 = p1->getParent();
    
    UfNodeList ufnlist;
    while (p1 != p2) {
        ufnlist.push_back(n);
        n = p1;
        p1 = p2;
        p2 = p2->getParent();
    }
    
    for (auto& n : ufnlist) {
        n->setParent(p2);
    }
    return p2;
}

inline unsigned long UfNode::hammingDist(UfNode* n, size_t width) {
    return ::hammingDist(getData(), n->getData(), width);
}

inline void UfNode::reverseBits(size_t width) {
    m_data = ::reverseBits(m_data, width);
}

inline void UfNode::dumpBits(std::ostream& o, size_t width) {
    ::dumpBits(o, m_data, width);
}

////////////////////////////////////////////////////////////////////////////////
// class to hold all the data-structures
class Cluster {
public:
    Cluster() {}
    ~Cluster();
    
public:
    bool read(const std::string& filename);
    bool readSize(std::ifstream& ifstr);
    bool readUf(std::ifstream& ifstr);
    
public:
    void dumpHammingDist(std::ostream& o, int v1, int v2);
    bool dumpUf(std::ostream& o, UfNode* n, bool all = false);
    bool dumpUf(std::ostream& o, int v1, int v2, bool all = false);
    void dumpUfs(std::ostream& o);
    void dumpParent(std::ostream& o, int v1, int v2);
    void dumpNodes(std::ostream &o);

public: // Algorithms
    unsigned long hammingDist(int v1, int v2);
    void merge(int v1, int v2);
    bool compress(int v1, int v2);
    void cluster(int maxDist);
    int clusterCount();
    
private:
    int m_items;
    int m_width;
    UfNodeVec m_nodes;
    UfNodeList m_uf;
};

////////////////////////////////////////////////////////////////////////////////
// Implementation
inline Cluster::~Cluster() {
    for (auto& n : m_nodes) {
        delete n;
    }
}

inline bool Cluster::readSize(std::ifstream& ifstr) {
    std::string line;
    std::getline(ifstr, line);
    if (! ifstr.good()) {
        return false;
    }
    std::stringstream istr(line);
    istr >> m_items >> m_width;
    return true;
}

inline bool Cluster::readUf(std::ifstream& ifstr) {
    std::string line;
    std::getline(ifstr, line);
    if (! ifstr.good()) {
        return false;
    }
    std::stringstream istr(line);
    int bit, data = 0;
    for (int i = 0; i < m_width; i++) {
        istr >> bit;
        data |= (bit << i);
    }
    UfNode* n = new UfNode(data);
    n->reverseBits(m_width);
    m_nodes.push_back(n);
    m_uf.push_back(n);
   return true;
}

inline bool Cluster::read(const std::string& filename) {
    std::ifstream ifstr(filename);
    if (! ifstr.good()) {
        std::cout << "ERROR: Could not read \"" << filename << "\"" << std::endl;
        return false;
    }
    // Get graph size
    if (! readSize(ifstr)) {
        return false;
    }
    
    while (readUf(ifstr));
    return false;
}

inline void Cluster::dumpHammingDist(std::ostream& o, int v1, int v2) {
    UfNode* n1 = m_nodes[v1];
    UfNode* n2 = m_nodes[v2];
    if (n1 == nullptr || n2 == nullptr) {
        return;
    }
    unsigned long dist = n1->hammingDist(n2, m_width);
    n1->dumpBits(o, m_width);
    o << std::endl;
    n2->dumpBits(o, m_width);
    o << std::endl;
    o << "hd=" << dist << std::endl;
}

inline bool Cluster::dumpUf(std::ostream &o, UfNode* n, bool all) {
    if (n == nullptr) {
        return false;
    }
    UfNode* p = n->findParent();
    if (n == p) {
        std::cout << "*";
    } else {
        if (! all) {
            return false;
        }
        o << " ";
    }
    o << "v=";
    n->dumpBits(o, m_width);
    o << " (r=" << n->getRank() << ")";
    
    if (n != p) {
        o << " [v=";
        p->dumpBits(o, m_width);
        o << " (r=" << p->getRank() << ")]";
    }
    return true;
}

inline bool Cluster::dumpUf(std::ostream& o, int v1, int v2, bool all) {
    UfNode* n1 = m_nodes[v1];
    UfNode* n2 = m_nodes[v2];
    o << "{";
    bool rc1 = dumpUf(o, n1, all);
    o << "}{";
    bool rc2 = dumpUf(o, n2, all);
    o << "}";
    return rc1 && rc2;
}

inline void Cluster::dumpUfs(std::ostream &o) {
    for(auto& uf : m_uf) {
        if (dumpUf(o, uf)) {
            o << std::endl;
        }
    }
}

inline void Cluster::dumpNodes(std::ostream &o) {
    for(auto& n : m_nodes) {
        if (dumpUf(o, n)) {
            o << std::endl;
        }
    }
    o << std::endl;
    int count = clusterCount();
    o << "[count=" << count << "]";
    o << std::endl;
}

inline void Cluster::dumpParent(std::ostream& o, int v1, int v2) {
    UfNode* n1 = m_nodes[v1];
    UfNode* n2 = m_nodes[v2];
    UfNode* p1 = n1->findParent();
    UfNode* p2 = n2->findParent();
    o << "{";
    dumpUf(o, p1);
    o << "}";
    if (p1 != p2) {
        o << " {";
        dumpUf(o, p2);
        o << "}";
    }
}

inline unsigned long Cluster::hammingDist(int v1, int v2) {
    UfNode* n1 = m_nodes[v1];
    UfNode* n2 = m_nodes[v2];
    if (n1 == nullptr || n2 == nullptr) {
        return std::numeric_limits<unsigned long>::max();
    }
    return n1->hammingDist(n2, m_width);
}

inline void Cluster::merge(int v1, int v2) {
    UfNode* n1 = m_nodes[v1];
    UfNode* n2 = m_nodes[v2];
    UfNode* p1 = n1->findParent();
    UfNode* p2 = n2->findParent();
    int r1 = p1->getRank();
    int r2 = p2->getRank();
    
    if (r1 > r2) {
        n2->setParent(p1);
        p2->setParent(p1);
    } else if (r1 < r2) {
        n1->setParent(p2);
        p1->setParent(p2);
    } else { // r1 == r2
        n2->setParent(p1);
        p2->setParent(p1);
        p1->incrRank();
    }
}

inline bool Cluster::compress(int v1, int v2) {
    UfNode* n1 = m_nodes[v1];
    UfNode* n2 = m_nodes[v2];
    UfNode* p1 = n1->compress();
    UfNode* p2 = n2->compress();
    return p1 == p2;
}

inline void Cluster::cluster(int maxDist) {
    for (int i = 0; i < m_nodes.size(); i++) {
        for (int j = i; j < m_nodes.size(); j++) {
            if (i == j) {
                continue;
            }
            for (int d = 0; d < maxDist; d++) {
                unsigned long dist = hammingDist(i, j);
                if (dist <= d) {
                    merge(i, j);
                    compress(i, j);
                }
            }
        }
    }
}

int Cluster::clusterCount() {
    int count = 0;
    for(auto& uf : m_uf) {
        count += uf == uf->getParent();
    }
    return count;
}

////////////////////////////////////////////////////////////////////////////////
//
int main(int argc, const char * argv[]) {
////////////////////////////////////////////////////////////////////////////////
// 6118
    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering-big/clustering_big.txt");
// 2
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering-big/clustering_big2.txt");
// 6
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering-big/clustering_big3.txt");
    
// 3
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering-big/input_random_1_4_14.txt");
// 3
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering-big/input_random_2_4_10.txt");
// 1017
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering-big/input_random_52_1024_24.txt");
// 736
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering-big/input_random_74_16384_20.txt");
// 37
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering-big/input_random_78_32768_20.txt");
// 1371
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering-big/input_random_80_65536_22.txt");
// 2549
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering-big/input_random_83_262144_24.txt");

    Cluster c;
    c.read(filename);
//    c.dumpHammingDist(std::cout, 0, 1);
//    c.dumpHammingDist(std::cout, 1, 2);
//    c.dumpHammingDist(std::cout, 2, 3);
//    c.dumpHammingDist(std::cout, 3, 4);
    
    c.cluster(3);
    c.dumpNodes(std::cout);

    return 0;
}
