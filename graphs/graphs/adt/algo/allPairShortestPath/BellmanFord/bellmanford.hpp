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

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
class bellmanford {
public: // Aliases
using Matrix = std::array<std::vector<int>, 2>;
using Path = std::vector<int>;

public: // Constructors/destructors
    explicit bellmanford(const adt::graph<DV, DE>& g);
    ~bellmanford();
    
public: // Utilities
    bool odd(int n) const;
    void init(int sv);
    void dump(std::ostream& o) const;
    void dumpSpValue(std::ostream& o) const;
    void dumpPath(std::ostream& o) const;

public: // Algorithms
    int computeSpMatrix(int sv);
    void computePath();
    int run(int sv);
    int run();

public: // Operators
    int operator()(int sv);
    int operator()();

public: // Accessors
    const adt::graph<DV, DE>& graph() const { return m_graph; }
    const Matrix& matrix() const { return m_matrix; }
    const Path& path() const { return m_path; }
    int spVertex() const { return m_spVertex; }
    int spIndex() const { return m_spIndex; }
    int spValue() const { return m_spValue; }

protected: // Accessors
    Matrix& matrix() { return m_matrix; }
    Path& path() { return m_path; }
    int spVertex() { return m_spVertex; }
    int spIndex() { return m_spIndex; }
    int spValue() { return m_spValue; }
    void spVertex(int spv) { m_spVertex = spv; }
    void spIndex(int idx) { m_spIndex = idx; }
    void spValue(int val) { m_spValue = val; }

private:
    const adt::graph<DV, DE>& m_graph;
    Matrix m_matrix;
    Path m_path;
    int m_spVertex;
    int m_spIndex;
    int m_spValue;
};

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
std::ostream& operator<< (std::ostream& o, bellmanford<DV, DE>& bf) {
    bf.dump(o);
    return o;
}

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
bellmanford<DV, DE>::bellmanford(const adt::graph<DV, DE>& g) : m_graph(g),
    m_spVertex(-1), m_spIndex(-1), m_spValue(PosInf) {
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
    matrix()[0].resize(graph().vertices().size(), PosInf);
    matrix()[1].resize(graph().vertices().size(), PosInf);
    matrix()[0][sv] = 0;
}

template <typename DV, typename DE>
int bellmanford<DV, DE>::computeSpMatrix(int sv) {
    init(sv);
    
    bool match = true;
    int icurr = -1;
    int iprev = -1;
    Matrix& m = matrix();
    const VertexVec<DV, DE>& vVec = graph().vertices();
	const int vsz = static_cast<int>(graph().vertices().size());
	const int esz = static_cast<int>(graph().edges().size());
    int i = 1;
    for (; i < esz + 1; i++) { // + 1 to detect -ve cost cycle
        match = true;
        for (int v = 1; v < vsz; v++) {
            icurr = odd(i);
            iprev = !odd(i);
            
            int pm = PosInf;
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
                    if (pval == PosInf) {
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
    
    spIndex(icurr);
    int res = PosInf;
    if (match) {
        for (int v = 1; v < vsz; v++) {
            int val = m[icurr][v];
            if (val < res) {
                res = val;
                spVertex(v);
                spValue(val);
            }
        }
    } else {
        res = NegInf;
    }
    
    return res;
}

template <typename DV, typename DE>
void bellmanford<DV, DE>::computePath() {
    path().clear();
    graph().resetVertices();
    Matrix& m = matrix();
    const VertexVec<DV, DE>& vVec = graph().vertices();
    
    int icurr = spIndex();
    int v = spVertex();
    
    while (v > 0) {
        const vertex<DV, DE>* vptr = vVec[v];
        if (vptr == nullptr) {
            return;
        }
        if (vptr->isVisited()) {
            return;
        }
        vptr->markVisited();
        path().push_back(v);

        int w = -1;
        v = w;
        int minval = PosInf;

        const EdgeVec<DV, DE>& eVec = vptr->fanin();
        for (auto eptr : eVec) {
            const vertex<DV, DE>* bptr = eptr->back();
            if (bptr == nullptr) {
                continue;
            }
            w = bptr->id();
            int wval = m[icurr][w];
            if (wval < minval) {
                minval = wval;
                v = w;
            }
        }
    }
}

template <typename DV, typename DE>
int bellmanford<DV, DE>::run(int sv) {
    return computeSpMatrix(sv);
}

template <typename DV, typename DE>
int bellmanford<DV, DE>::run() {
	const int vsz = static_cast<int>(graph().vertices().size());
    int rmin = PosInf;
    for (int v = 1; v < vsz; v++) {
        int res = computeSpMatrix(v);
        if (res == NegInf) {
            return res;
        }
        if (rmin > res) {
            rmin = res;
            computePath();
        }
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

template <typename DV, typename DE>
void bellmanford<DV, DE>::dump(std::ostream& o) const {
    dumpSpValue(o);
    o << ": ";
    dumpPath(o);
}

template <typename DV, typename DE>
void bellmanford<DV, DE>::dumpSpValue(std::ostream& o) const {
    dumpVal(o, spValue());
}

template <typename DV, typename DE>
void bellmanford<DV, DE>::dumpPath(std::ostream& o) const {
	const int psz = static_cast<int>(path().size());
    o << "[";
    for (int i = 0; i < psz; i++) {
        int v = path()[psz - i - 1];
        if (i > 0) {
            o << ", ";
        }
        o << v;
    }
    o << "]";
}

};

#endif /* bellmanford_hpp */
