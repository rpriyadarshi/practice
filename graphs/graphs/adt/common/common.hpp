//
//  common.h
//  graphs
//
//  Created by Rohit Priyadarshi on 2/22/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#ifndef common_h
#define common_h

////////////////////////////////////////////////////////////////////////////////
namespace adt {
    
template <typename DV, typename DE>
class edge;
template <typename DV, typename DE>
class vertex;
template <typename DV, typename DE>
class graph;

// Aliases
template <typename DV, typename DE>
using EdgeAlloc = std::allocator<edge<DV, DE>*>;
template <typename DV, typename DE>
using VertexAlloc = std::allocator<vertex<DV, DE>*>;
template <typename DV, typename DE>
using EdgeVec = std::vector<edge<DV, DE>*, EdgeAlloc<DV, DE>>;
template <typename DV, typename DE>
using VertexVec = std::vector<vertex<DV, DE>*, VertexAlloc<DV, DE>>;
    
};

#endif /* common_h */
