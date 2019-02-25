//
//  edge.hpp
//  graphs
//
//  Created by Rohit Priyadarshi on 2/22/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#ifndef edge_hpp
#define edge_hpp

////////////////////////////////////////////////////////////////////////////////
namespace adt {
    
    ////////////////////////////////////////////////////////////////////////////
    template <typename DV, typename DE>
    class edge {
    public: // Constructors/destructors
        edge();
        edge(vertex<DV, DE>* f, vertex<DV, DE>* b);
        ~edge();
        
    private: // Accessors
        const vertex<DV, DE>* front() const { return m_front; }
        const vertex<DV, DE>* back() const { return m_back; }
        const DE& data() const { return m_data; }
        
    protected: // Accessors
        vertex<DV, DE>* front() { return m_front; }
        vertex<DV, DE>* back() { return m_back; }
        DE& data() { return m_data; }

    protected: // Accessors
        void front(vertex<DV, DE>* v) { m_front = v; }
        void back(vertex<DV, DE>* v) { m_back = v; }
        
    private:
        vertex<DV, DE>* m_front;
        vertex<DV, DE>* m_back;
        DE m_data;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    template <typename DV, typename DE>
    edge<DV, DE>::edge() : m_front(nullptr), m_back(nullptr) {
    }
    
    template <typename DV, typename DE>
    edge<DV, DE>::edge(vertex<DV, DE>* f, vertex<DV, DE>* b) : m_front(f), m_back(b) {
    }
    
    template <typename DV, typename DE>
    edge<DV, DE>::~edge() {
    }
    
};

#endif /* edge_hpp */
