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
using Matrix = std::array<std::vector<std::vector<int>>, 3>;
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
    int spBVertex() const { return m_spBVertex; }
    int spFVertex() const { return m_spFVertex; }
    int spIndex() const { return m_spIndex; }
    int spValue() const { return m_spValue; }

protected: // Accessors
    Matrix& matrix() { return m_matrix; }
    Path& path() { return m_path; }
    int spBVertex() { return m_spBVertex; }
    int spFVertex() { return m_spFVertex; }
    int spIndex() { return m_spIndex; }
    int spValue() { return m_spValue; }
    void spBVertex(int spv) { m_spBVertex = spv; }
    void spFVertex(int spv) { m_spFVertex = spv; }
    void spIndex(int idx) { m_spIndex = idx; }
    void spValue(int val) { m_spValue = val; }

private:
    const adt::graph<DV, DE>& m_graph;
    Matrix m_matrix;
    Path m_path;
    int m_spBVertex;
    int m_spFVertex;
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
    m_spBVertex(-1), m_spFVertex(-1), m_spIndex(-1), m_spValue(PosInf) {
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
    m[2].resize(sz);

    for (int i = 0; i < sz; i++) {
        m[0][i].resize(sz, PosInf);
        m[1][i].resize(sz, PosInf);
        m[2][i].resize(sz, NegInf);
        m[0][i][i] = 0;
    }
    
    for (auto eptr : graph().edges()) {
        const vertex<DV, DE>* bptr = eptr->back();
        const vertex<DV, DE>* fptr = eptr->front();
        const DE& de = eptr->data();
        m[0][bptr->id()][fptr->id()] = std::min(m[0][bptr->id()][fptr->id()], de.data());
        m[2][bptr->id()][fptr->id()] = bptr->id();
    }
}

template <typename DV, typename DE>
int floydwarshall<DV, DE>::computeSpMatrix() {
    init();

    Matrix& m = matrix();
    size_t sz = graph().vertices().size();

    int kcurr = -1;
    int kprev = -1;
    for (int k = 1; k < sz; k++) {
        kcurr = odd(k);
        kprev = !odd(k);
        for (int i = 1; i < sz; i++) {
            for (int j = 1; j < sz; j++) {
                int pvalc1 = m[kprev][i][j];
                int pval1 = m[kprev][i][k];
                int pval2 = m[kprev][k][j];
                int pvalc2 = 0;
                if (pval1 == PosInf ||
                    pval2 == PosInf) {
                    pvalc2 = PosInf;
                } else if (pval1 == NegInf ||
                    pval2 == NegInf) {
                    pvalc2 = NegInf;
                } else {
                    pvalc2 = pval1 + pval2;
                }
                
                int pval = 0;
                if (pvalc1 > pvalc2) {
                    pval = pvalc2;
                    m[2][i][j] = m[2][k][j];
                } else {
                    pval = pvalc1;
                }
                
                m[kcurr][i][j] = pval;
            }
        }
    }
    
    spIndex(kcurr);
    int res = PosInf;
    for (int i = 1; i < sz; i++) {
        for (int j = 1; j < sz; j++) {
            int val = m[kcurr][i][j];
            if (i == j) {
                if (val < 0) {
                    return NegInf;
                } else {
                    continue;
                }
            } else if (val < res) {
                res = val;
                spBVertex(i);
                spFVertex(j);
                spValue(val);
            }
        }
    }
    
    return res;
}

template <typename DV, typename DE>
void floydwarshall<DV, DE>::computePath() {
    int u = spBVertex();
    int v = spFVertex();
    const Matrix& m = matrix();
    
    path().clear();
    path().push_back(v);
    while(u != v) {
        v = m[2][u][v];
        path().push_back(v);
    }
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
    size_t sz = graph().vertices().size();
    const Matrix& m = matrix();
    for (int i = 1; i < sz; i++) {
        for (int j = 1; j < sz; j++) {
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
