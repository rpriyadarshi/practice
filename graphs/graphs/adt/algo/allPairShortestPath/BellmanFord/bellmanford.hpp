//
//  bellmanford.hpp
//  graphs
//
//  Created by Rohit Priyadarshi on 2/28/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#ifndef bellmanford_hpp
#define bellmanford_hpp

////////////////////////////////////////////////////////////////////////////////
namespace adt {

using Matrix = std::array<std::vector<int>, 2>;

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
class bellmanford {
public: // Constructors/destructors
    explicit bellmanford(const adt::graph<DV, DE>& g);
    ~bellmanford();
    
public: // Utilities
    bool odd(int n) const;
    void init(int sv);
    
public: // Algorithms
    int run(int sv);
    int run();

public: // Operators
    int operator()(int sv);
    int operator()();

public: // Accessors
    const graph<DV, DE>& graph() const { return m_graph; }
    const Matrix& matrix() const { return m_matrix; }

protected: // Accessors
    Matrix& matrix() { return m_matrix; }

private:
    const adt::graph<DV, DE>& m_graph;
    Matrix m_matrix;
};

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
bellmanford<DV, DE>::bellmanford(const adt::graph<DV, DE>& g) : m_graph(g) {
}

template <typename DV, typename DE>
bellmanford<DV, DE>::~bellmanford() {
}

template <typename DV, typename DE>
bool bellmanford<DV, DE>::odd(int n) const {
    return n & 0x1;
}

template <typename DV, typename DE>
void bellmanford<DV, DE>::init(int sv) {
    matrix()[0].resize(graph().vertices().size(), std::numeric_limits<int>::max());
    matrix()[1].resize(graph().vertices().size(), std::numeric_limits<int>::max());
    matrix()[0][sv] = 0;
}

template <typename DV, typename DE>
int bellmanford<DV, DE>::run(int sv) {
    init(sv);
    
    bool match = true;
    int icurr = -1;
    int iprev = -1;
    Matrix& m = matrix();
    const VertexVec<DV, DE>& vVec = graph().vertices();
    int i = 1;
    for (; i < graph().edges().size() + 1; i++) { // + 1 to detect -ve cost cycle
        match = true;
        for (int v = 1; v < graph().vertices().size(); v++) {
            icurr = odd(i);
            iprev = !odd(i);
            
            int pm = std::numeric_limits<int>::max();
            const vertex<DV, DE>* vptr = vVec[v];
            
            // Unused vertex index unless the implementation is switched to
            // an unordered_map
            if (vptr == nullptr) {
                continue;
            }
            const EdgeVec<DV, DE>& eVec = vptr->fanin();
            for (auto eptr : eVec) {
                const vertex<DV, DE>* bptr = eptr->back();
                if (bptr != nullptr) {
                    const DE& de = eptr->data();
                    int cost = de.data();
                    int pval = m[iprev][bptr->id()];
                    if (pval == std::numeric_limits<int>::max()) {
                        continue;
                    }
                    int val = pval + cost;
                    pm = std::min(pm, val);
                }
            }
            
            m[icurr][v] = std::min(m[iprev][v], pm);
            if (m[icurr][v] != m[iprev][v]) {
                match = false;
            }
        }
        if (match) {
            break;
        }
    }
    
    if (i < graph().edges().size() - 1) {
        std::cout << "Early result found (" << i << " : " << graph().edges().size() - 1 << ")" << std::endl;
    }
    
    if (match) {
//        std::cout << "Match found " << i << std::endl;
    } else {
        std::cout << "Mismatch found " << i << std::endl;
    }
    
    int res = std::numeric_limits<int>::max();
    for (auto val : m[icurr]) {
        res = std::min(val, res);
    }
    
    return res;
}

template <typename DV, typename DE>
int bellmanford<DV, DE>::run() {
    int rmin = std::numeric_limits<int>::max();
    for (int v = 1; v < graph().vertices().size(); v++) {
        int res = run(v);
        rmin = std::min(rmin, res);
    }
    
    return rmin;
}

template <typename DV, typename DE>
int bellmanford<DV, DE>::operator()(int sv) {
    return run(sv);
}

template <typename DV, typename DE>
int bellmanford<DV, DE>::operator()() {
    return run();
}

};

#endif /* bellmanford_hpp */
