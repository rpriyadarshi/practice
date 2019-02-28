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
    
////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
class edge {
public: // Constructors/destructors
    explicit edge(unsigned int idx);
    edge(unsigned int idx, vertex<DV, DE>* f, vertex<DV, DE>* b);
    ~edge();
    
public: // Utility functions
    void connect();
    void dump(std::ostream& o) const;
    
public: // Accessors
    unsigned int id() const { return m_id; }
    const vertex<DV, DE>* front() const { return m_front; }
    const vertex<DV, DE>* back() const { return m_back; }
    DE& data() const { return m_data; }

public: // Accessors
    unsigned int id() { return m_id; }
    vertex<DV, DE>* front() { return m_front; }
    vertex<DV, DE>* back() { return m_back; }

protected: // Accessors
    void front(vertex<DV, DE>* v) { m_front = v; }
    void back(vertex<DV, DE>* v) { m_back = v; }
    
private:
    unsigned int m_id;
    vertex<DV, DE>* m_front;
    vertex<DV, DE>* m_back;
    mutable DE m_data;
};

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
std::ostream& operator<< (std::ostream& o, edge<DV, DE>& e) {
    e.dump(o);
    return o;
}

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
edge<DV, DE>::edge(unsigned int idx)
: m_id(idx), m_front(nullptr), m_back(nullptr) {
}

template <typename DV, typename DE>
edge<DV, DE>::edge(unsigned int idx, vertex<DV, DE>* fv, vertex<DV, DE>* bv)
: m_id(idx), m_front(fv), m_back(bv) {
}

template <typename DV, typename DE>
edge<DV, DE>::~edge() {
}

template <typename DV, typename DE>
void edge<DV, DE>::connect() {
    vertex<DV, DE>* fptr = front();
    vertex<DV, DE>* bptr = back();
    if (fptr) {
        fptr->fanin(this);
    }
    if (bptr) {
        bptr->fanout(this);
    }
}


template <typename DV, typename DE>
void edge<DV, DE>::dump(std::ostream& o) const {
    const vertex<DV, DE>* bptr = back();
    const vertex<DV, DE>* fptr = front();
    if (bptr != nullptr) {
        o << bptr->id();
    } else {
        o << "nullptr";
    }
    o << " ";
    if (fptr != nullptr) {
        o << fptr->id();
    } else {
        o << "nullptr";
    }
    o << " ";
    o << data();
}
    
};

#endif /* edge_hpp */
