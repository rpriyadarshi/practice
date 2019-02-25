//
//  main.cpp
//  graphs
//
//  Created by Rohit Priyadarshi on 2/22/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#include "adt.hpp"

class Data {
public:
    Data() : m_data(0) {}
    ~Data() {}
    
private:
    int m_data;
};

class vData : public Data {
public:
    vData() : Data() {}
    ~vData() {}
};

class eData : public Data {
public:
    eData() : Data() {}
    ~eData() {}
};


int main(int argc, const char * argv[]) {
    adt::factory fac;
    adt::graph<vData, eData> g;
    adt::vertex<vData, eData>* v1 = g.createVertex(fac);
    adt::vertex<vData, eData>* v2 = g.createVertex(fac);
    adt::edge<vData, eData>* e = g.createEdge(v1, v2, fac);

    return 0;
}
