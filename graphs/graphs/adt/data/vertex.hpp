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
    
    ////////////////////////////////////////////////////////////////////////////
    template <typename DV, typename DE>
    class vertex {
    public: // Constructors/destructors
        vertex();
        ~vertex();
        
    public: // Accessors
        const EdgeVec<DV, DE>& fanin() const { return m_fanin; }
        const EdgeVec<DV, DE>& fanout() const { return m_fanout; }
        const DV& data() const { return m_data; }

    protected: // Accessors
        EdgeVec<DV, DE>& fanin() { return m_fanin; }
        EdgeVec<DV, DE>& fanout() { return m_fanout; }
        DV& data() { return m_data; }
        
    private:
        EdgeVec<DV, DE> m_fanin;
        EdgeVec<DV, DE> m_fanout;
        DV m_data;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    template <typename DV, typename DE>
    vertex<DV, DE>::vertex() {
    }
    
    template <typename DV, typename DE>
    vertex<DV, DE>::~vertex() {
    }
};

#endif /* vertex_hpp */
