//
//  tensor.hpp
//  n-dimensional-tensor
//
//  Created by Rohit Priyadarshi on 3/3/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#ifndef tensor_hpp
#define tensor_hpp

namespace nten {

/*******************************************************************************
    The data-structure and algorithm: Since Tensor is an N-dimenstional matrix,
    we will build a matrix and extennd it for N dimensions.
 
    Review the idea in tensorindexing.png. This outlines tensor indexing
    index = dn*(D1*D2*...*Dn-1) + dn-1*(D1*D2*...*Dn-2) + ... + d2*(D1) + d1
 
    Build a product vector as follows:
    PDn = D1*D2*...*Dn-1
    PDn-1 = D1*D2*...*Dn-2
    ...
    PD2 = D1
    PD1 = 1
 
    Now this can be iteratively precomputed:
    PDn = PDn-1 * Dn-1
    PDn-1 = PDn-2 * Dn-2
    ...
    PD3 = PD2 * D2
    PD2 = PD1 * D1
    PD1 = 1
 
    index = dn*PDn + dn-1*PDn-1 + ... + d1*PD1
 
    1. Compute +/- 1 indexes and add the values to get a total_value
       (Similer to indexTree function)
    2. mean = total_value/#elements
    3. save the mean on the index
 
    TBD --
    1. Change recursive indexing functions to iterative. This will help using
       the navigational mechanism for more than 1 purpose (mean calculation)
    2. The item 1 above leads to creation of const/non-const iterators
    3. Allocation of memory in the class is not a good idea. These must be
       managed separately for performance
    4. The algorithm used is brute force. Performance measurements on large
       datasets may be in order.
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
template<typename F>
class tensor {
public: // Constructors/destructors
    tensor(const float* data, const UIntVec& evec);
    ~tensor();
    
public: // calculations
    float* calculateMean();
    
public: // Utility
    void build();
    void indexTree(UIntVec& idx);
    void indexTree(UIntVec& idx, unsigned int loc);
    unsigned int envelope(const UIntVec& atIdx, UIntVec& idx, float& val);
    unsigned int envelope(const UIntVec& atIdx, UIntVec& idx, unsigned int loc, float& val);
    unsigned int callIndex(const UIntVec& atIdx, unsigned int loc);
    unsigned int callEnvelope(const UIntVec& atIdx, unsigned int loc, float& val);
    void calculatePdVec();
    void calculateSize();
    void enableDebug() { debug(true); }
    void disableDebug() { debug(false); }

public: // Accessors
    unsigned int size() const { return m_size; }
    const float* cache() const { return m_cache; }
    const float* data() const { return m_data; }
    const UIntVec& extVec() const { return m_extVec; }
    const UIntVec& pdVec() const { return m_pdVec; }
    const F& func() const { return m_func; }
    bool debug() const { return m_debug; }

protected: // Accessors
    unsigned int size() { return m_size; }
    float* cache() { return m_cache; }
    UIntVec& pdVec() { return m_pdVec; }
    F& func() { return m_func; }
    bool debug() { return m_debug; }
    void size(unsigned int s) { m_size = s; }
    void cache(float* cf) { m_cache = cf; }
    void debug(bool d) { m_debug = d; }
    
private:
    unsigned int m_size;
    float* m_cache;
    const float* m_data;
    const UIntVec& m_extVec;
    UIntVec m_pdVec;
    F m_func;
    bool m_debug;
};

////////////////////////////////////////////////////////////////////////////////
template<typename F>
tensor<F>::tensor(const float* data, const UIntVec& evec)
    : m_size(0), m_cache(nullptr), m_data(data), m_extVec(evec),
    m_func(m_pdVec), m_debug(false) {
}

template<typename F>
tensor<F>::~tensor() {
    delete [] m_cache;
}

// Consolidates building and book keeping
template<typename F>
void tensor<F>::build() {
    calculatePdVec();
    calculateSize();
    unsigned int sz = size();
    float* fc = new float[sz];
    std::memset(fc, 0.0, sz * sizeof(float));
    cache(fc);
}

// Run the indexer. Must be converted to an inerator
template<typename F>
void tensor<F>::indexTree(UIntVec& idx) {
    indexTree(idx, 0);
}

template<typename F>
void tensor<F>::indexTree(UIntVec& idx, unsigned int loc) {
    int ext = extVec()[loc];
    for (int i = 0; i < ext; i++) {
        idx[loc] = i;
        callIndex(idx, loc);
        int nextloc = loc + 1;
        if (nextloc < extVec().size()) {
            indexTree(idx, nextloc);
        }
    }
};

// Run the envelop, given a location. Must be converted to an inerator
template<typename F>
unsigned int tensor<F>::envelope(const UIntVec& atIdx, UIntVec& idx, float& val) {
    return envelope(atIdx, idx, 0, val);
}

template<typename F>
unsigned int tensor<F>::envelope(const UIntVec& atIdx, UIntVec& idx, unsigned int loc, float& val) {
    unsigned int cells = 0;
    int ext = extVec()[loc];
    int ival = atIdx[loc];
    int ib = std::max(ival - 1, 0);
    int ie = std::min(ival + 1, ext - 1);
    
    for (int i = ib; i <= ie; i++) {
        idx[loc] = i;
        cells += callEnvelope(idx, loc, val);
        int nextloc = loc + 1;
        if (nextloc < extVec().size()) {
            cells += envelope(atIdx, idx, nextloc, val);
        }
    }
    return cells;
};

// Index tree termination point. Runs anvelope here
template<typename F>
unsigned int tensor<F>::callIndex(const UIntVec& atIdx, unsigned int loc) {
    if (loc != extVec().size() - 1) {
        return 0;
    }
    
    float* cf = cache();
    UIntVec idx(atIdx.size(), 0);
    float val = 0.0;
    
    unsigned int ival = func().index(atIdx);
    unsigned int cells = envelope(atIdx, idx, val);
    float mean = val / cells;
    cf[ival] = mean;
    
    if (debug()) {
        std::cout << "location: [";
        func().dump(std::cout, atIdx);
        std::cout << "], cells: [" << cells << ", " << val << ", " << mean << "]" << std::endl;
    }
    
    return 1;
}

// Gather the value from input tensor
template<typename F>
unsigned int tensor<F>::callEnvelope(const UIntVec& atIdx, unsigned int loc, float& val) {
    if (loc != extVec().size() - 1) {
        return 0;
    }

    unsigned int ival = func().index(atIdx);
    if (data()) {
        val += data()[ival];
    }
    return 1;
}

// Small optimization to prevent repeated multiplications
template<typename F>
void tensor<F>::calculatePdVec() {
    const UIntVec& extvec = extVec();
    UIntVec& pdvec = pdVec();
    pdvec.resize(extvec.size());
    pdvec[0] = 1;
    for (int i = 1; i < extvec.size(); i++) {
        pdvec[i] = pdvec[i - 1] * extvec[i - 1];
    }
}

// Precompute tensor size
template<typename F>
void tensor<F>::calculateSize() {
    unsigned int sz = 1;
    const UIntVec& extvec = extVec();
    for (auto ev : extvec) {
        sz *= ev;
    }
    size(sz);
}

// Run mean computation
template<typename F>
float* tensor<F>::calculateMean() {
    UIntVec idx(extVec().size(), 0);
    build();
    indexTree(idx);
    return cache();
}

};

#endif /* tensor_hpp */
