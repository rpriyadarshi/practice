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
 
    TBD --
    1. Compute +/- 1 indexes and add the values to get a total_value
       (Similer to indexTree function)
    2. mean = total_value/#elements
    3. save the mean on the index
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
template<typename F>
class tensor {
public: // Constructors/destructors
    tensor(const float* data, const UIntVec& evec);
    ~tensor();
    
public: // Utility
    void indexTree(UIntVec& idx);
    void indexTree(UIntVec& idx, unsigned int loc);
    unsigned int envelope(const UIntVec& atIdx, UIntVec& idx);
    unsigned int envelope(const UIntVec& atIdx, UIntVec& idx, unsigned int loc);
    unsigned int callIndex(const UIntVec& atIdx, unsigned int loc);
    unsigned int callEnvelope(const UIntVec& atIdx, unsigned int loc);
    void calculatePdVec();
    
public: // Accessors
    const float* data() { return m_data; }
    const UIntVec& extVec() const { return m_extVec; }
    const UIntVec& pdVec() const { return m_pdVec; }
    const F& func() const { return m_func; }

protected: // Accessors
    UIntVec& pdVec() { return m_pdVec; }
    F& func() { return m_func; }

private:
    const float* m_data;
    const UIntVec& m_extVec;
    UIntVec m_pdVec;
    F m_func;
};

////////////////////////////////////////////////////////////////////////////////
template<typename F>
tensor<F>::tensor(const float* data, const UIntVec& evec)
    : m_data(data), m_extVec(evec), m_func(m_pdVec) {
    calculatePdVec();
}

template<typename F>
tensor<F>::~tensor() {
}

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

template<typename F>
unsigned int tensor<F>::envelope(const UIntVec& atIdx, UIntVec& idx) {
    return envelope(atIdx, idx, 0);
}

template<typename F>
unsigned int tensor<F>::envelope(const UIntVec& atIdx, UIntVec& idx, unsigned int loc) {
    unsigned int cells = 0;
    int ext = extVec()[loc];
    int ival = atIdx[loc];
    int ib = std::max(ival - 1, 0);
    int ie = std::min(ival + 1, ext);
    
    for (int i = ib; i <= ie; i++) {
        idx[loc] = i;
        cells += callEnvelope(idx, loc);
        int nextloc = loc + 1;
        if (nextloc < extVec().size()) {
            cells += envelope(atIdx, idx, nextloc);
        }
    }
    return cells;
};

template<typename F>
unsigned int tensor<F>::callIndex(const UIntVec& atIdx, unsigned int loc) {
    if (loc != extVec().size() - 1) {
        return 0;
    }
    func()(atIdx);
    return 1;
}

template<typename F>
unsigned int tensor<F>::callEnvelope(const UIntVec& atIdx, unsigned int loc) {
    if (loc != extVec().size() - 1) {
        return 0;
    }
    func()(atIdx);
    return 1;
}

template<typename F>
void tensor<F>::calculatePdVec() {
    const UIntVec& extvec = extVec();
    UIntVec& pdvec = pdVec();
    pdvec.resize(extvec.size());
    pdvec[0] = 1;
    for (int i = 1; i < extvec.size(); i++) {
        pdvec[i] = pdvec[i - 1] * extvec[i - 1];
    }
    
//    for (auto ev : extvec) {
//        std::cout << ev << " ";
//    }
//    std::cout << std::endl;
//    for (auto pd : pdvec) {
//        std::cout << pd << " ";
//    }
//    std::cout << std::endl;
}

};

#endif /* tensor_hpp */
