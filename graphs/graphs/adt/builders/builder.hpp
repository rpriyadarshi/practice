//
//  builder.hpp
//  graphs
//
//  Created by Rohit Priyadarshi on 2/24/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#ifndef builder_hpp
#define builder_hpp

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
    // Edge based
    bool readSize(std::ifstream& ifstr);
    bool readEdges(std::ifstream& ifstr, adt::factory& fac);
    bool readEdges(const std::string& filename, adt::factory& fac);
    
    // Adjacency list based
    bool readSizeFromEnd(std::ifstream& ifstr);
    bool readAdjList(std::ifstream& ifstr, adt::factory& fac);
    bool readAdjList(const std::string& filename, adt::factory& fac);

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
        
        int v2idx, v1idx, cost;
        sstr >> v2idx >> v1idx >> cost;
        graph().createEdge(idx++, v1idx, v2idx, cost, fac);
    }
    
    return idx != 0;
}

template <typename DV, typename DE>
bool builder<DV, DE>::readEdges(const std::string& filename, adt::factory& fac) {
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
bool builder<DV, DE>::readSizeFromEnd(std::ifstream& ifstr) {
    std::string line(getlastline(ifstr));
    std::stringstream sstr(line);
    int vSize;
    sstr >> vSize;
    graph().resize(vSize);
    return true;
}

template <typename DV, typename DE>
bool builder<DV, DE>::readAdjList(std::ifstream& ifstr, adt::factory& fac) {
    int idx = 0;
    std::string line, head, tok, ver, len;
    ifstr.clear();
    ifstr.seekg(0, std::ios::beg);
    while (std::getline(ifstr, line).good()) {
        std::stringstream strstr(line);
        strstr >> head;
        int fval = std::stoi(head);
        while (strstr >> tok) {
            size_t pos = tok.find(",");
            if (pos == std::string::npos) {
                continue;
            }
            ver = tok.substr(0, pos++);
            len = tok.substr(pos, std::string::npos);
            
            int tval = std::stoi(ver);
            int cost = std::stoi(len);
            
            graph().createEdge(idx++, fval, tval, cost, fac);
        }
    }
    return true;
}

template <typename DV, typename DE>
bool builder<DV, DE>::readAdjList(const std::string& filename, adt::factory& fac) {
    std::ifstream ifstr(filename);
    if (! ifstr.good()) {
        std::cout << "ERROR: Cannot read " << filename << std::endl;
        return false;
    }
    
    bool rc = readSizeFromEnd(ifstr);
    if (rc) {
        rc = readAdjList(ifstr, fac);
    }

    return rc;
}

template <typename DV, typename DE>
void builder<DV, DE>::dump(std::ostream& o) const {
}

};

#endif /* builder_hpp */
