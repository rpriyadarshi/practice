//
//  main.cpp
//  prims
//
//  Created by Rohit Priyadarshi on 10/29/18.
//  Copyright © 2018 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <vector>
#include <limits>
#include <queue>
#include <set>

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
template <typename T, typename C> class Heap {
public: // Constructors/destructors
    Heap() {}
    ~Heap() {}
    
public: // heap APIs
    T pop();
    void push(T val);
    void push_back(T val);
    void heapify();
    
public: // helpers
    bool empty() const;
    void dump(std::ostream& o) const;
    
public: // Accessors
    const std::vector<T>& data() const;
    
private:
    std::vector<T> m_data;
    C m_cmp;
};

template <typename T, typename C>
T Heap<T, C>::pop() {
    std::pop_heap(m_data.begin(), m_data.end(), m_cmp);
    T t = m_data.back();
    m_data.pop_back();
    return t;
}

template <typename T, typename C>
void Heap<T, C>::push(T val) {
    std::push_heap(m_data.begin(), m_data.end(), m_cmp);
    m_data.push_back(val);
}

template <typename T, typename C>
void Heap<T, C>::push_back(T val) {
    m_data.push_back(val);
}

template <typename T, typename C>
void Heap<T, C>::heapify() {
    std::make_heap(m_data.begin(), m_data.end(), m_cmp);
}

template <typename T, typename C>
bool Heap<T, C>::empty() const {
    return m_data.empty();
}

template <typename T, typename C>
const std::vector<T>& Heap<T, C>::data() const {
    return m_data;
}

template <typename T, typename C>
void Heap<T, C>::dump(std::ostream& o) const {
    for (auto d : m_data) {
        std::cout << d << " ";
    }
    o << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
class Vertex {
public: // Constructors/destructors
    explicit Vertex(int id) : m_id(id), m_visited(false),
    m_key(std::numeric_limits<int>::max()) {}
    ~Vertex() {}
    
public: // Accessors
    int getId() const { return m_id; }
    int getKey() const { return m_key; }
    bool isVisited() const { return m_visited; }
    const EdgeList& getEdges() const { return m_edges; }
    
public: // Accessors
    void setVisited(bool v) { m_visited = v; }
    void setKey(int key) { m_key = key; }
    EdgeList& getEdges() { return m_edges; }
    
private: // data
    int m_id;
    bool m_visited;
    mutable int m_key;
    EdgeList m_edges;
};

////////////////////////////////////////////////////////////////////////////////
class VertexCmp {
public: // operators
    bool operator() (const Vertex* l, const Vertex* r) {
        return l->getKey() > r->getKey();
    }
};

////////////////////////////////////////////////////////////////////////////////
// Typedefs
//typedef std::priority_queue<Vertex*, VertexVec, VertexCmp> PQueue;
//typedef std::multiset<Vertex*, VertexCmp> PQueue;
//typedef std::vector<Vertex*> PQueue;
typedef Heap<Vertex*, VertexCmp> PQueue;

////////////////////////////////////////////////////////////////////////////////
class Edge {
public: // Constructor/destructor
    Edge(Vertex* v, int wt) : m_ver(v), m_cost(wt) {}
    ~Edge() {}
    
public: // Accessors
    const Vertex* getVer() const { return m_ver; }
    int getCost() const { return m_cost; }
    
public: // Accessors
    Vertex* getVer() { return m_ver; }
    void setCost(int cost) { m_cost = cost; }
    
private: // data
    Vertex* m_ver;
    int m_cost;
};

////////////////////////////////////////////////////////////////////////////////
class Graph {
public: // Constructor/destructor
    explicit Graph(const std::string& filename);
    ~Graph() {}
    
public: // Algorithms
    int mst();
    Vertex* init();
    Vertex* runOne();
    
public: // Utility functions
    bool read();
    void dumpQueue(std::ostream& o = std::cout) const;
    void dumpGraph(std::ostream& o = std::cout) const;
    
public: // data
    const std::string m_filename;
    VertexVec m_table;
    PQueue m_pq;
};

inline Graph::Graph(const std::string& filename) :  m_filename(filename) {
    std::ifstream ifstr(m_filename);
    if (! ifstr.good()) {
        std::cout << "ERROR: Cannot load file \"" << m_filename << std::endl;
        return;
    }
    
    std::string line;
    if (!std::getline(ifstr, line).good()) {
        return;
    }
    int numNodes, numEdges;
    std::stringstream strstr(line);
    strstr >> numNodes;
    strstr >> numEdges;

    size_t sz = numNodes + 1;
    m_table.resize(sz);
    for (int i = 0; i < sz; i++) {
        m_table.at(i) = new Vertex(i);
    }
}

inline bool Graph::read() {
    std::ifstream ifstr(m_filename);
    if (! ifstr.good()) {
        return false;
    }
    
    std::string line;
    if (std::getline(ifstr, line).good()) {
        int numNodes, numEdges;
        std::stringstream strstr(line);
        strstr >> numNodes;
        strstr >> numEdges;
    }
    int locV1, locV2, cost;
    while (std::getline(ifstr, line).good()) {
        std::stringstream strstr(line);
        strstr >> locV1;
        strstr >> locV2;
        strstr >> cost;
        
        Vertex* v1 = m_table.at(locV1);
        Vertex* v2 = m_table.at(locV2);
        
        EdgeList& el1 = v1->getEdges();
        EdgeList& el2 = v2->getEdges();
        
        el1.push_back(new Edge(v2, cost));
        if (v1 != v2) {
            el2.push_back(new Edge(v1, cost));
        }
    }
    return true;
}

inline Vertex* Graph::init() {
    int loc = static_cast<int>(m_table.size()) / 2;
    Vertex* s = m_table[loc];
    s->setVisited(true);
    for (auto& e : s->getEdges()) {
        Vertex* v = e->getVer();
        int key = std::min(v->getKey(), e->getCost());
        v->setKey(key);
    }
    for (int i = 1; i < m_table.size(); i++) {
        Vertex* v = m_table[i];
        if (s == v) continue;
        m_pq.push_back(v);
    }
    m_pq.heapify();
    return s;
}

inline Vertex* Graph::runOne() {
//    dumpQueue(std::cout);
    Vertex* vt = m_pq.pop();
//    dumpQueue(std::cout);
    if (vt->isVisited()) {
        return 0;
    }
    vt->setVisited(true);
    for (auto& e : vt->getEdges()) {
        Vertex* v = e->getVer();
        int key = std::min(v->getKey(), e->getCost());
        v->setKey(key);
    }
    m_pq.heapify();
    return vt;
}

inline int Graph::mst() {
    int cost = 0;
    Vertex* s = init();
    std::cout << s->getId() << "[" << s->getKey() << "]" << std::endl;
    while (! m_pq.empty()) {
        Vertex* v = runOne();
        if (v) {
            cost += v->getKey();
            std::cout << v->getId() << "[" << v->getKey() << "]" << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << cost << std::endl;
    return cost;
}

inline void Graph::dumpQueue(std::ostream& o) const {
    for (int i = 0; i < m_pq.data().size(); i++) {
        const Vertex* d = m_pq.data()[i];
        if (i) o << ", ";
        o << d->getId() << "["<< d->getKey() << "]";
    }
    o << std::endl;
}

inline void Graph::dumpGraph(std::ostream& o) const {
    for (int i = 0; i < m_table.size(); i++) {
        std::cout << i << "\t";
        Vertex* v = m_table.at(i);
        EdgeList& el = v->getEdges();
        for (auto e : el) {
            std::cout << "->" << e->getVer()->getId() << " [" << e->getCost() << "] ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    // -3612829
    const std::string filename("/Users/rohit/Documents/Development/practice/prims/edges.txt");
    // 7
//    const std::string filename("/Users/rohit/Documents/Development/practice/prims/small_edges.txt");
    // 14
//    const std::string filename("/Users/rohit/Documents/Development/practice/prims/small_edges2.txt");
    // 15
//    const std::string filename("/Users/rohit/Documents/Development/practice/prims/small_edges3.txt");
//    const std::string filename("/Users/rohit/Documents/Development/practice/prims/small_edges4.txt");
    // -7430
//    const std::string filename("/Users/rohit/Documents/Development/practice/prims/input_random_1_10.txt");
#if 1
    Graph g(filename);
    
    g.read();

//    g.dumpGraph();
    g.mst();
#else
    Heap<int, std::greater<int>> heap;
#if 0
    heap.push_back(1);
    heap.push_back(10);
    heap.push_back(-5);
    heap.push_back(7);
    heap.push_back(8);
    heap.push_back(-8);
    heap.push_back(-8);
    heap.heapify();
#else
    heap.push(1);
    heap.push(10);
    heap.push(-5);
    heap.push(7);
    heap.push(8);
    heap.push(-8);
    heap.push(-8);
#endif
    heap.dump(std::cout);
    while (! heap.empty()) {
        std::cout << heap.pop() << " ";
    }
    std::cout << std::endl;
#endif
    return 0;
}
