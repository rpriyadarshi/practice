//
//  graph.hpp
//  graphs
//
//  Created by Rohit Priyadarshi on 2/22/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

////////////////////////////////////////////////////////////////////////////////
namespace adt {
    
////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
class graph {
public: // Constructors/destructors
    graph();
    ~graph();
    
public: // Create
    vertex<DV, DE>* createVertex(unsigned int id, factory& fac);
    edge<DV, DE>* createEdge(unsigned int id, vertex<DV, DE>* v1, vertex<DV, DE>* v2, factory& fac);

public: // Utility functions
    void resize(unsigned int v, unsigned int e);
    void resetVertices() const;
    void dump(std::ostream& o) const;
    void dumpVertexVec(std::ostream& o) const;
    void dumpEdgeVec(std::ostream& o) const;

public: // Accessors
    const VertexVec<DV, DE>& vertices() const { return m_vertices; }
    const EdgeVec<DV, DE>& edges() const { return m_edges; }

protected: // Accessors
    VertexVec<DV, DE>& vertices() { return m_vertices; }
    EdgeVec<DV, DE>& edges() { return m_edges; }
    
private:
    VertexVec<DV, DE> m_vertices;
    EdgeVec<DV, DE> m_edges;
};

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
std::ostream& operator<< (std::ostream& o, graph<DV, DE>& g) {
    g.dump(o);
    return o;
}

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
graph<DV, DE>::graph() {
}

template <typename DV, typename DE>
graph<DV, DE>::~graph() {
}

template <typename DV, typename DE>
void graph<DV, DE>::resize(unsigned int v, unsigned int e) {
    vertices().resize(v);
    edges().resize(e);
}

template <typename DV, typename DE>
vertex<DV, DE>*
graph<DV, DE>::createVertex(unsigned int id, factory& fac) {
    if (vertices().size() <= id) {
        vertices().resize(id + 1);
    }
    vertex<DV, DE>* ptr = nullptr;
    try {
        ptr = vertices().at(id);
        if (ptr == nullptr) {
            vertex<DV, DE> v(id);
            ptr = fac.create(v);
            vertices().at(id) = ptr;
        }
    }
    catch (std::out_of_range& e) {
        std::cout << "ERROR: " << e.what() << " out of range" << std::endl;
    }
    return ptr;
}

template <typename DV, typename DE>
edge<DV, DE>*
graph<DV, DE>::createEdge(unsigned int id, vertex<DV, DE>* v1, vertex<DV, DE>* v2, factory& fac) {
    if (edges().size() <= id) {
        edges().resize(id + 1);
    }
    edge<DV, DE>* ptr = nullptr;
    try {
        ptr = edges().at(id);
        if (ptr == nullptr) {
            edge<DV, DE> e(id, v1, v2);
            ptr = fac.create(e);
            ptr->connect();
            edges().at(id) = ptr;
        }
    }
    catch (std::out_of_range& e) {
        std::cout << "ERROR: " << e.what() << " out of range" << std::endl;
    }
    return ptr;
}

template <typename DV, typename DE>
void graph<DV, DE>::resetVertices() const {
    for (auto vptr : vertices()) {
        if (vptr != nullptr) {
            vptr->clearVisited();
        }
    }
}

template <typename DV, typename DE>
void graph<DV, DE>::dump(std::ostream& o) const {
    dumpVertexVec(o);
}

template <typename DV, typename DE>
void graph<DV, DE>::dumpEdgeVec(std::ostream& o) const {
    for (int i = 0; i < edges().size(); i++) {
        edge<DV, DE>* e = edges()[i];
        if (e == nullptr) {
            o << i << " nullptr" << std::endl;
        } else {
            o << *e << std::endl;
        }
    }
}

template <typename DV, typename DE>
void graph<DV, DE>::dumpVertexVec(std::ostream& o) const {
    for (int i = 0; i < vertices().size(); i++) {
        vertex<DV, DE>* v = vertices()[i];
        if (v == nullptr) {
            o << i << " nullptr" << std::endl;
        } else {
            o << *v << std::endl;
        }
    }
}

};

#endif /* graph_hpp */
