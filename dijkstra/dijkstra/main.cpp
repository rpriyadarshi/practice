//
//  main.cpp
//  dijkstra
//
//  Created by Rohit Priyadarshi on 6/29/18.
//  Copyright © 2018 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <vector>
#include <limits>
#include <queue>

////////////////////////////////////////////////////////////////////////////////
// Forward declarations
class Edge;
class Vertex;

////////////////////////////////////////////////////////////////////////////////
// Typedefs
typedef std::list<Edge*> EdgeList;
typedef std::vector<Vertex*> VertexVec;
typedef std::vector<Edge*> EdgeVec;

////////////////////////////////////////////////////////////////////////////////
class Vertex {
public: // Constructors/destructors
    explicit Vertex(int id) : m_id(id), m_visited(false),
    m_tot(1000000/*std::numeric_limits<int>::max()*/) {}
    ~Vertex() {}
    
public: // Accessors
    int getId() const { return m_id; }
    int getTot() const { return m_tot; }
    bool isVisited() const { return m_visited; }
    const EdgeList& getEdges() const { return m_edges; }

public: // Accessors
    void setVisited(bool v) { m_visited = v; }
    void setTot(int tot) { m_tot = tot; }
    EdgeList& getEdges() { return m_edges; }

private: // data
    int m_id;
    bool m_visited;
    mutable int m_tot;
    EdgeList m_edges;
};

////////////////////////////////////////////////////////////////////////////////
class VertexCmp {
public: // operators
    bool operator() (Vertex* l, Vertex* r) { return l->getTot() > r->getTot(); }
};

////////////////////////////////////////////////////////////////////////////////
// Typedefs
typedef std::priority_queue<Vertex*, VertexVec, VertexCmp> PQueue;

////////////////////////////////////////////////////////////////////////////////
class Edge {
public: // Constructor/destructor
    Edge(Vertex* v, int wt) : m_ver(v), m_wt(wt) {}
    ~Edge() {}
    
public: // Accessors
    const Vertex* getVer() const { return m_ver; }
    int getWt() const { return m_wt; }
    
public: // Accessors
    Vertex* getVer() { return m_ver; }
    void setWt(int wt) { m_wt = wt; }

private: // data
    Vertex* m_ver;
    int m_wt;
};

////////////////////////////////////////////////////////////////////////////////
class Graph {
public: // Constructor/destructor
    explicit Graph(size_t sz);
    ~Graph() {}
    
public: // Algorithms
    void fsp(int idx);
    
public: // Utility functions
    bool read(const std::string& filename);
    void dumpGraph(std::ostream& o = std::cout);
    void dumpWeights(std::ostream& o = std::cout);
    void dumpAsgn2(std::ostream& o = std::cout);

public: // data
    VertexVec m_table;
};

inline Graph::Graph(size_t sz) : m_table(sz) {
    for (int i = 0; i < sz; i++) {
        m_table.at(i) = new Vertex(i);
    }
}

inline bool Graph::read(const std::string& filename) {
    std::ifstream ifstr(filename);
    if (! ifstr.good()) {
        return false;
    }
    
    std::string line, head, tok, ver, len;
    while (std::getline(ifstr, line).good()) {
        std::stringstream strstr(line);
        strstr >> head;
        int hval = std::stoi(head);
        Vertex* v = m_table.at(hval);
        EdgeList& el = v->getEdges();
        while (strstr >> tok) {
            size_t pos = tok.find(",");
            if (pos == std::string::npos) {
                continue;
            }
            ver = tok.substr(0, pos++);
            len = tok.substr(pos, std::string::npos);
            
            int vval = std::stoi(ver);
            int lval = std::stoi(len);
            Vertex* vl = m_table.at(vval);
            el.push_back(new Edge(vl, lval));
        }
    }
    return true;
}

inline void Graph::dumpGraph(std::ostream& o) {
    for (int i = 0; i < m_table.size(); i++) {
        std::cout << i << "\t";
        Vertex* v = m_table.at(i);
        EdgeList& el = v->getEdges();
        for (auto e : el) {
            std::cout << e->getVer()->getId() << "," << e->getWt() << " ";
        }
        std::cout << std::endl;
    }
}

inline void Graph::dumpWeights(std::ostream& o) {
    for (auto v : m_table) {
        std::cout << v->getId() << ": " << v->getTot() << std::endl;
    }
}

inline void Graph::dumpAsgn2(std::ostream& o) {
    int idx[] {7,37,59,82,99,115,133,165,188,197};
    for (auto i : idx) {
        Vertex* v = m_table.at(i);
        std::cout << v->getTot() << ",";
    }
    std::cout << std::endl;
}

inline void Graph::fsp(int idx) {
    PQueue q;
    int pwt = 0;
    
    Vertex* v0 = m_table.at(idx);
    v0->setTot(0);
    EdgeList& el = v0->getEdges();
    for (auto e : el) {
        Vertex* v1 = e->getVer();
        int wt = pwt + e->getWt();
        int mwt = std::min(wt, v1->getTot());
        v1->setTot(mwt);
        q.push(v1);
    }
    while (! q.empty()) {
        Vertex* v0 = q.top();
        q.pop();
        
        pwt = v0->getTot();
        v0->setVisited(true);
        
        EdgeList& el = v0->getEdges();
        for (auto e : el) {
            Vertex* v1 = e->getVer();
            int wt = pwt + e->getWt();
            int mwt = std::min(wt, v1->getTot());
            v1->setTot(mwt);
            if (v1->isVisited())
                continue;
            q.push(v1);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
#if 1
    const std::string filename("/Users/rohit/Documents/Development/practice/dijkstra/dijkstraData.txt");
    Graph g(201);
#else
    const std::string filename("/Users/rohit/Documents/Development/practice/dijkstra/dijkstraSmallData.txt");
    Graph g(8);
#endif
    
    g.read(filename);
    g.fsp(1);
    
    g.dumpGraph();
    g.dumpWeights();
    g.dumpAsgn2();

    return 0;
}
