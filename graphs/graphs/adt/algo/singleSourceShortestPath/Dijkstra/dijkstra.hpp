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
class dijkstra {
public: // Aliases

public: // Constructors/destructors
    explicit dijkstra(const adt::graph<DV, DE>& g);
    ~dijkstra();
}

};

#endif /* dijkstra_hpp */
