//
//  builder.hpp
//  graphs
//
//  Created by Rohit Priyadarshi on 2/24/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#ifndef edgebuilder_hpp
#define edgebuilder_hpp

////////////////////////////////////////////////////////////////////////////////
namespace adt {

////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
class builder {
public: // Constructors/destructors
    builder(adt::graph<DV, DE>& g);
    ~builder();
    
public: // Utility functions
    void dump(std::ostream& o) const;
    
public: // Accessors
    const adt::graph<DV, DE>& graph() const { return m_graph; }
    
protected: // Accessors
    adt::graph<DV, DE>& graph() { return m_graph; }
    
public: // Readers
    bool read(const std::string& filename, adt::factory& fac);
    bool readSize(std::ifstream& ifstr);
    bool readEdges(std::ifstream& ifstr, adt::factory& fac);

private:
    adt::graph<DV, DE>& m_graph;
};

////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
builder<DV, DE>::builder(adt::graph<DV, DE>& g) : m_graph(g) {
}

template <typename DV, typename DE>
builder<DV, DE>::~builder() {
}

// The first line indicates the number of vertices and edges, respectively.
// Each subsequent line describes an edge (the first two numbers are its
// tail and head, respectively) and its length (the third number).
template <typename DV, typename DE>
bool builder<DV, DE>::readSize(std::ifstream& ifstr) {
    std::string line;
    
    // Read sizes; num vertices and num edges
    std::getline(ifstr, line);
    std::stringstream sstr(line);
    int vSize, eSize;
    sstr >> vSize >> eSize;
    graph().resize(vSize, eSize);
    
    return true;
}

template <typename DV, typename DE>
bool builder<DV, DE>::readEdges(std::ifstream& ifstr, adt::factory& fac) {
    std::string line;
    int idx = 0;
    while (std::getline(ifstr, line)) {
        std::stringstream sstr(line);
        
        int tail, head, length;
        sstr >> tail >> head >> length;
        adt::vertex<DV, DE>* vt = graph().createVertex(tail, fac);
        adt::vertex<DV, DE>* vh = graph().createVertex(head, fac);
        adt::edge<DV, DE>* e = graph().createEdge(idx++, vh, vt, fac);
        DE& de = e->data();
        de.data(length);
    }
    
    return idx != 0;
}

template <typename DV, typename DE>
bool builder<DV, DE>::read(const std::string& filename, adt::factory& fac) {
    std::ifstream ifstr(filename);
    if (! ifstr.good()) {
        std::cout << "ERROR: Cannot read " << filename << std::endl;
        return false;
    }
    
    bool rc = readSize(ifstr);
    if (rc) {
        rc = readEdges(ifstr, fac);
    }
    
    return rc;
}

template <typename DV, typename DE>
void builder<DV, DE>::dump(std::ostream& o) const {
}

};

#endif /* edgebuilder_hpp */
