//
//  main.cpp
//  max-spacing-k-clustering
//
//  Created by Rohit Priyadarshi on 12/27/18.
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

////////////////////////////////////////////////////////////////////////////////
class Edge;
class UfNode;

////////////////////////////////////////////////////////////////////////////////
typedef std::vector<Edge*> EdgeVec;
typedef std::vector<EdgeVec> EdgeVecVec;
typedef std::list<UfNode*> UfNodeList;
typedef std::vector<UfNode*> UfNodeVec;

////////////////////////////////////////////////////////////////////////////////
// Edge class maintains both vertices
class Edge {
public:
    Edge() : m_v1(0), m_v2(0), m_cost(0) {}
    Edge(int v1, int v2, int cost) : m_v1(v1), m_v2(v2), m_cost(cost) {}
    ~Edge() {}
    
public: // Accessors
    int getCost() const { return m_cost; }
    int getV1() const { return m_v1; }
    int getV2() const { return m_v2; }

public: // Accessors
    int getCost() { return m_cost; }
    int getV1() { return m_v1; }
    int getV2() { return m_v2; }

private:
    int m_cost;
    int m_v1;
    int m_v2;
};

////////////////////////////////////////////////////////////////////////////////
//
struct {
    bool operator()(Edge* e1, Edge* e2) {
        return e1->getCost() < e2->getCost();
    }
} EdgeLess;

////////////////////////////////////////////////////////////////////////////////
// class to build Union-Find data-structure
class UfNode {
public:
    explicit UfNode(int id) : m_id(id), m_parent(this), m_rank(0) {}
    ~UfNode() {}
    
public:
    void incrRank() { m_rank++; }
    UfNode* findParent();
    UfNode* compress();

public:
    int getId() const { return m_id; }
    UfNode* getParent() const { return m_parent; }
    int getRank() const { return m_rank; }
    
public:
    int getId() { return m_id; }
    UfNode* getParent() { return m_parent; }
    int getRank() { return m_rank; }
    void setParent(UfNode* n) { m_parent = n; }

private:
    int m_id;
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

////////////////////////////////////////////////////////////////////////////////
// class to hold all the data-structures
class Graph {
public:
    Graph() : m_maxEdge(nullptr) {}
    ~Graph();
    
public:
    bool readSmall(const std::string& filename);
    bool readBig(const std::string& filename);
    bool readSize(std::ifstream& ifstr);
    bool readEdge(std::ifstream& ifstr);
    
public:
    bool dumpEdge(std::ostream& o, Edge* e);
    bool dumpUf(std::ostream& o, UfNode* n, bool all = false);
    bool dumpUf(std::ostream& o, int v1, int v2, bool all = false);
    bool dumpUf(std::ostream& o, Edge* e, bool all = false);
    void dumpGraph(std::ostream& o);
    void dumpEdges(std::ostream& o);
    void dumpUfs(std::ostream& o);
    void dumpParent(std::ostream& o, int v1, int v2);
    void dumpParent(std::ostream& o, Edge* e);

public: // Algorithms
    void sortEdges();
    void merge(int v1, int v2);
    void merge(Edge* e);
    bool compress(int v1, int v2);
    bool compress(Edge* e);
    bool sameCluster(int v1, int v2);
    bool sameCluster(Edge* e);
    void cluster(int k);
    int clusterCount();

private:
    EdgeVec m_edges;
    UfNodeVec m_nodes;
    EdgeVecVec m_graph;
    UfNodeList m_uf;
    Edge* m_maxEdge;
};

////////////////////////////////////////////////////////////////////////////////
// Implementation
inline Graph::~Graph() {
    for (auto& e : m_edges) {
        delete e;
    }
    for (auto& n : m_nodes) {
        delete n;
    }
}

inline bool Graph::readSize(std::ifstream& ifstr) {
    std::string line;
    std::getline(ifstr, line);
    if (! ifstr.good()) {
        return false;
    }
    std::stringstream istr(line);
    int size;
    istr >> size;
    m_graph.resize(size + 1);
    m_nodes.resize(size + 1);
    return true;
}

inline bool Graph::readEdge(std::ifstream& ifstr) {
    std::string line;
    std::getline(ifstr, line);
    if (! ifstr.good()) {
        return false;
    }
    std::stringstream istr(line);
    int v1, v2, cost;
    istr >> v1 >> v2 >> cost;
    Edge* e = new Edge(v1, v2, cost);
    m_edges.push_back(e);
    m_graph[v1].push_back(e);
    m_graph[v2].push_back(e);
    if (!m_nodes[v1]) {
        m_nodes[v1] = new UfNode(v1);
        m_uf.push_back(m_nodes[v1]);
    }
    if (!m_nodes[v2]) {
        m_nodes[v2] = new UfNode(v2);
        m_uf.push_back(m_nodes[v2]);
    }
    return true;
}

inline bool Graph::readSmall(const std::string& filename) {
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

inline bool Graph::readBig(const std::string& filename) {
    return false;
}

inline bool Graph::dumpEdge(std::ostream &o, Edge* e) {
    if (e == nullptr) {
        return false;
    }
    std::cout << "c=" << e->getCost() << " [v1=" << e->getV1() << " v2=" << e->getV2() << "]";
    return true;
}

inline bool Graph::dumpUf(std::ostream &o, UfNode* n, bool all) {
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
        std::cout << " ";
    }
    std::cout << "v=" << n->getId() << " (r=" << n->getRank() << ")";
    if (n != p) {
        std::cout << " [v=" << p->getId() << " (r=" << p->getRank() << ")]";
    }
    return true;
}

inline void Graph::dumpGraph(std::ostream &o) {
    for(auto& ev : m_graph) {
        for (auto& e : ev) {
            if (dumpEdge(o, e)) {
                o << std::endl;
            }
        }
    }
    o << std::endl;
}

inline void Graph::dumpEdges(std::ostream &o) {
    for (auto& e : m_edges) {
        if (dumpEdge(o, e)) {
            o << std::endl;
        }
    }
    o << std::endl;
}

inline bool Graph::dumpUf(std::ostream& o, int v1, int v2, bool all) {
    UfNode* n1 = m_nodes[v1];
    UfNode* n2 = m_nodes[v2];
    o << "{";
    bool rc1 = dumpUf(o, n1, all);
    o << "}{";
    bool rc2 = dumpUf(o, n2, all);
    o << "}";
    return rc1 && rc2;
}

inline bool Graph::dumpUf(std::ostream& o, Edge* e, bool all) {
    if (!e) return false;
    return dumpUf(o, e->getV1(), e->getV2(), all);
}

inline void Graph::dumpUfs(std::ostream &o) {
    for(auto& uf : m_uf) {
        if (dumpUf(o, uf)) {
            o << std::endl;
        }
    }
    if (dumpEdge(o, m_maxEdge)) {
        o << std::endl;
    }
}

inline void Graph::dumpParent(std::ostream& o, int v1, int v2) {
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

inline void Graph::dumpParent(std::ostream& o, Edge* e) {
    if (!e) return;
    return dumpParent(o, e->getV1(), e->getV2());
}

inline void Graph::sortEdges() {
    std::sort(m_edges.begin(), m_edges.end(), EdgeLess);
}

inline void Graph::merge(int v1, int v2) {
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

inline void Graph::merge(Edge* e) {
    if (!e) return;
    merge(e->getV1(), e->getV2());
}

inline bool Graph::sameCluster(int v1, int v2) {
    UfNode* n1 = m_nodes[v1];
    UfNode* n2 = m_nodes[v2];
    UfNode* p1 = n1->compress();
    UfNode* p2 = n2->compress();
    return p1 == p2;
}

inline bool Graph::sameCluster(Edge* e) {
    if (!e) return false;
    return sameCluster(e->getV1(), e->getV2());
}

inline bool Graph::compress(int v1, int v2) {
    UfNode* n1 = m_nodes[v1];
    UfNode* n2 = m_nodes[v2];
    UfNode* p1 = n1->compress();
    UfNode* p2 = n2->compress();
    return p1 == p2;
}

inline bool Graph::compress(Edge* e) {
    if (!e) return false;
    return compress(e->getV1(), e->getV2());
}

inline void Graph::cluster(int k) {
    int count = clusterCount();
    for (auto& e : m_edges) {
        if (count <= k && ! sameCluster(e)) {
            m_maxEdge = e;
            
            std::cout << "[count=" << count << "] ";
            dumpEdge(std::cout, e);
            std::cout << "[break]" << std::endl;
            break;
        }
        merge(e);
        compress(e);
        count = clusterCount();

        std::cout << "[count=" << count << "] ";
        dumpEdge(std::cout, e);
        std::cout << " p=";
        dumpParent(std::cout, e);
        std::cout << std::endl;
    }
}

int Graph::clusterCount() {
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
//    c=106 [v1=414 v2=455]
    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/clustering1.txt");
// K = 2 --> 5, K = 3 --> 2, K = 4 --> 1
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/clustering2.txt");
// K = 2 -> 8, K = 3 -> 4, K = 4 -> 1
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/clustering3.txt");
    
// k=4, 21
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/input_completeRandom_1_8.txt");
// k=4, 6
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/input_completeRandom_2_8.txt");
// k=4, 11
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/input_completeRandom_3_8.txt");
// k=4, 17
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/input_completeRandom_4_8.txt");

// k=4, 29
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/input_completeRandom_5_16.txt");
// k=4, 25
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/input_completeRandom_6_16.txt");

// k=4, 100
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/input_completeRandom_11_32.txt");
// k=4, 431
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/input_completeRandom_19_128.txt");
// k=4, 1157
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/input_completeRandom_21_256.txt");
// k=4, 6720
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/input_completeRandom_31_1024.txt");

////////////////////////////////////////////////////////////////////////////////
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/clustering_big.txt");
// 2
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/clustering_big2.txt");
// 6
//    std::string filename("/Users/rohit/Documents/Development/practice/max-spacing-k-clustering/clustering_big3.txt");

    Graph g;
    g.readSmall(filename);
//    g.dumpGraph(std::cout);
//    std::cout << std::endl;
    
    g.sortEdges();
//    g.dumpEdges(std::cout);
//    std::cout << std::endl;

    g.cluster(4);
    
    std::cout << std::endl;
    g.dumpUfs(std::cout);
    std::cout << std::endl;
    return 0;
}
