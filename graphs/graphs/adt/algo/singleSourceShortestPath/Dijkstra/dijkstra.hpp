//
//  dijkstra.hpp
//  graphs
//
//  Created by Rohit Priyadarshi on 3/15/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#ifndef dijkstra_hpp
#define dijkstra_hpp

////////////////////////////////////////////////////////////////////////////////
namespace adt {

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
class VertexCmp {
public: // operators
    bool operator() (vertex<DV, DE>* l, vertex<DV, DE>* r) { return l->cache() > r->cache(); }
};

////////////////////////////////////////////////////////////////////////////////
// Typedefs
template <typename DV, typename DE>
using VertexPQueue = std::priority_queue<vertex<DV, DE>*, VertexVec<DV, DE>, VertexCmp<DV, DE>>;

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
class dijkstra {
public: // Aliases

public: // Constructors/destructors
    explicit dijkstra(const adt::graph<DV, DE>& g);
    ~dijkstra();
    
public: // Utilities
    void dump(std::ostream& o) const;

public: // Operators
    int operator()();

public: // Accessors
    const adt::graph<DV, DE>& graph() const { return m_graph; }

protected: // Accessors

private:
    const adt::graph<DV, DE>& m_graph;
};

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
std::ostream& operator<< (std::ostream& o, dijkstra<DV, DE>& fw) {
    fw.dump(o);
    return o;
}

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
dijkstra<DV, DE>::dijkstra(const adt::graph<DV, DE>& g) : m_graph(g) {
}

template <typename DV, typename DE>
dijkstra<DV, DE>::~dijkstra() {
}

template <typename DV, typename DE>
void dijkstra<DV, DE>::dump(std::ostream& o) const {
}

};

#endif /* dijkstra_hpp */
