//
//  floydwarshall.hpp
//  graphs
//
//  Created by Rohit Priyadarshi on 3/8/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#ifndef floydwarshall_hpp
#define floydwarshall_hpp

////////////////////////////////////////////////////////////////////////////////
namespace adt {

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
class floydwarshall {
public: // Aliases
using Matrix = std::array<std::vector<std::vector<int>>, 2>;
using Path = std::vector<int>;

public: // Constructors/destructors
    explicit floydwarshall(const adt::graph<DV, DE>& g);
    ~floydwarshall();
    
public: // Utilities
    bool odd(int n) const;
    void init();
    void dump(std::ostream& o) const;
    void dump(std::ostream& o, int k) const;
    void dumpSpValue(std::ostream& o) const;
    void dumpPath(std::ostream& o) const;

public: // Algorithms
    int computeSpMatrix();
    void computePath();
    int run();

public: // Operators
    int operator()();

public: // Accessors
    const graph<DV, DE>& graph() const { return m_graph; }
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
std::ostream& operator<< (std::ostream& o, floydwarshall<DV, DE>& fw) {
    fw.dump(o);
    return o;
}

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
floydwarshall<DV, DE>::floydwarshall(const adt::graph<DV, DE>& g) : m_graph(g),
    m_spVertex(-1), m_spIndex(-1), m_spValue(std::numeric_limits<int>::max()) {
}

template <typename DV, typename DE>
floydwarshall<DV, DE>::~floydwarshall() {
}

template <typename DV, typename DE>
bool floydwarshall<DV, DE>::odd(int n) const {
    return n & 0x1;
}

template <typename DV, typename DE>
void floydwarshall<DV, DE>::init() {
    size_t sz = graph().vertices().size();
    Matrix& m = matrix();
    m[0].resize(sz);
    m[1].resize(sz);
    
    for (int i = 0; i < sz; i++) {
        m[0][i].resize(sz, std::numeric_limits<int>::max());
        m[1][i].resize(sz, std::numeric_limits<int>::max());
        m[0][i][i] = 0;
    }
    
    for (auto eptr : graph().edges()) {
        const vertex<DV, DE>* bptr = eptr->back();
        const vertex<DV, DE>* fptr = eptr->front();
        const DE& de = eptr->data();
        m[0][bptr->id()][fptr->id()] = std::min(m[0][bptr->id()][fptr->id()], de.data());
    }
}

template <typename DV, typename DE>
int floydwarshall<DV, DE>::computeSpMatrix() {
    init();
    
    Matrix& m = matrix();
    
    int kcurr = -1;
    int kprev = -1;
    for (int k = 1; k < graph().vertices().size(); k++) {
        kcurr = odd(k);
        kprev = !odd(k);
        for (int i = 1; i < graph().vertices().size(); i++) {
            for (int j = 1; j < graph().vertices().size(); j++) {
                int pval0 = m[kprev][i][j];
                int pval1 = m[kprev][i][k];
                int pval2 = m[kprev][k][j];
                int pvals = 0;
                if (pval1 == std::numeric_limits<int>::max() ||
                    pval2 == std::numeric_limits<int>::max()) {
                    pvals = std::numeric_limits<int>::max();
                } else if (pval1 == std::numeric_limits<int>::min() ||
                    pval2 == std::numeric_limits<int>::min()) {
                    pvals = std::numeric_limits<int>::min();
                } else {
                    pvals = pval1 + pval2;
                }
                
                int pval = std::min(pval0, pvals);
                
                m[kcurr][i][j] = pval;
            }
        }
    }
    
    spIndex(kcurr);
    int res = std::numeric_limits<int>::max();
    for (int i = 1; i < graph().vertices().size(); i++) {
        for (int j = 1; j < graph().vertices().size(); j++) {
            int val = m[kcurr][i][j];
            if (i == j) {
                if (val < 0) {
                    return std::numeric_limits<int>::min();
                } else {
                    continue;
                }
            } else if (val < res) {
                res = val;
                spVertex(j);
                spValue(val);
            }
        }
    }

    return res;
}

template <typename DV, typename DE>
void floydwarshall<DV, DE>::computePath() {
    path().clear();
}

template <typename DV, typename DE>
int floydwarshall<DV, DE>::run() {
    int res = computeSpMatrix();
    computePath();
    return res;
}

template <typename DV, typename DE>
int floydwarshall<DV, DE>::operator()() {
    return run();
}

template <typename DV, typename DE>
void floydwarshall<DV, DE>::dump(std::ostream& o) const {
    dumpSpValue(o);
    o << ": ";
    dumpPath(o);
}

template <typename DV, typename DE>
void floydwarshall<DV, DE>::dump(std::ostream& o, int k) const {
    const Matrix& m = matrix();
    for (int i = 1; i < graph().vertices().size(); i++) {
        for (int j = 1; j < graph().vertices().size(); j++) {
            dumpVal(o, m[k][i][j]);
            o << " ";
        }
        o << std::endl;
    }
    o << std::endl;
}

template <typename DV, typename DE>
void floydwarshall<DV, DE>::dumpSpValue(std::ostream& o) const {
    dumpVal(o, spValue());
}

template <typename DV, typename DE>
void floydwarshall<DV, DE>::dumpPath(std::ostream& o) const {
    o << "[";
    for (int i = 0; i < path().size(); i++) {
        int v = path()[path().size() - i - 1];
        if (i > 0) {
            o << ", ";
        }
        o << v;
    }
    o << "]";
}

};

#endif /* floydwarshall_hpp */
