//
//  vertex.hpp
//  graphs
//
//  Created by Rohit Priyadarshi on 2/22/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#ifndef vertex_hpp
#define vertex_hpp

////////////////////////////////////////////////////////////////////////////////
namespace adt {
    
////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
class vertex {
public: // Constructors/destructors
    explicit vertex(unsigned int idx);
    ~vertex();
    
public: // Utility functions
    void dump(std::ostream& o) const;
    
public: // Accessors
    unsigned int id() const { return m_id; }
    const EdgeVec<DV, DE>& fanin() const { return m_fanin; }
    const EdgeVec<DV, DE>& fanout() const { return m_fanout; }
    DV& data() const { return m_data; }

protected: // Accessors
    unsigned int id() { return m_id; }
    EdgeVec<DV, DE>& fanin() { return m_fanin; }
    EdgeVec<DV, DE>& fanout() { return m_fanout; }
    
private:
    unsigned int m_id;
    EdgeVec<DV, DE> m_fanin;
    EdgeVec<DV, DE> m_fanout;
    mutable DV m_data;
};

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
std::ostream& operator<< (std::ostream& o, vertex<DV, DE>& v) {
    v.dump(o);
    return o;
}

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
vertex<DV, DE>::vertex(unsigned int idx) : m_id(idx) {
}

template <typename DV, typename DE>
vertex<DV, DE>::~vertex() {
}

template <typename DV, typename DE>
void vertex<DV, DE>::dump(std::ostream& o) const {
}
    
};

#endif /* vertex_hpp */
