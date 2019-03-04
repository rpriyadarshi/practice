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

////////////////////////////////////////////////////////////////////////////////
template<typename F>
class tensor {
public: // Constructors/destructors
    tensor(const float* data, const UIntVec& evec);
    ~tensor();
    
public: // Utility
    void indexTree(UIntVec& idx);
    void indexTree(UIntVec& idx, unsigned int loc);
    void callIndex(UIntVec& idx, unsigned int loc);
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
void tensor<F>::callIndex(UIntVec& idx, unsigned int loc) {
    if (loc != extVec().size() - 1) {
        return;
    }
    func()(idx);
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
