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
    
    ////////////////////////////////////////////////////////////////////////////
    template <typename DV, typename DE>
    class graph {
    public: // Constructors/destructors
        graph();
        ~graph();
        
    public: // Create
        vertex<DV, DE>* createVertex(factory& fac);
        edge<DV, DE>* createEdge(vertex<DV, DE>* v1, vertex<DV, DE>* v2, factory& fac);

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
    
    ////////////////////////////////////////////////////////////////////////////
    template <typename DV, typename DE>
    graph<DV, DE>::graph() {
    }
    
    template <typename DV, typename DE>
    graph<DV, DE>::~graph() {
    }
    
    template <typename DV, typename DE>
    vertex<DV, DE>*
    graph<DV, DE>::createVertex(factory& fac) {
        vertex<DV, DE> v;
        vertex<DV, DE>* ptr = fac.create(v);
        vertices().push_back(ptr);
        return ptr;
    }
    
    template <typename DV, typename DE>
    edge<DV, DE>*
    graph<DV, DE>::createEdge(vertex<DV, DE>* v1, vertex<DV, DE>* v2, factory& fac) {
        edge<DV, DE> e(v1, v2);
        edge<DV, DE>* ptr = fac.create(e);
        edges().push_back(ptr);
        return ptr;
    }

};

#endif /* graph_hpp */
