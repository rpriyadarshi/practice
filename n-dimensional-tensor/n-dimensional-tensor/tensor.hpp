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

using UIntVec = std::vector<unsigned int>;

class tensor {
public: // Constructors/destructors
    tensor(const float* data, const UIntVec& evec);
    ~tensor();
    
public: // Utility
    unsigned int index(const UIntVec& idx) const;
    void indexTree(UIntVec& idx);
    void indexTree(UIntVec& idx, unsigned int loc);
    void callIndex(UIntVec& idx, unsigned int loc);
    void calculatePdVec();
    
public: // Accessors
    const float* data() { return m_data; }
    const UIntVec& extVec() const { return m_extVec; }
    const UIntVec& pdVec() const { return m_pdVec; }

protected: // Accessors
    UIntVec& pdVec() { return m_pdVec; }

private:
    const float* m_data;
    const UIntVec& m_extVec;
    UIntVec m_pdVec;
};

inline tensor::tensor(const float* data, const UIntVec& evec)
    : m_data(data), m_extVec(evec) {
    calculatePdVec();
}

inline tensor::~tensor() {
}

inline void tensor::indexTree(UIntVec& idx) {
    indexTree(idx, 0);
}

inline void tensor::indexTree(UIntVec& idx, unsigned int loc) {
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

inline void tensor::callIndex(UIntVec& idx, unsigned int loc) {
    if (loc != extVec().size() - 1) {
        return;
    }
    std::cout << index(idx) << ": ";
    for (auto id: idx) {
        std::cout << id << " ";
    }
    std::cout << std::endl;
}

inline void tensor::calculatePdVec() {
    const UIntVec& extvec = extVec();
    UIntVec& pdvec = pdVec();
    pdvec.resize(extvec.size());
    pdvec[0] = 1;
    for (int i = 1; i < extvec.size(); i++) {
        pdvec[i] = pdvec[i - 1] * extvec[i - 1];
    }
    
    for (auto ev : extvec) {
        std::cout << ev << " ";
    }
    std::cout << std::endl;
    for (auto pd : pdvec) {
        std::cout << pd << " ";
    }
    std::cout << std::endl;
}

inline unsigned int tensor::index(const UIntVec& idx) const {
    const UIntVec& pdvec = pdVec();
    unsigned int flatidx = 0;
    for (int i = 0; i < idx.size(); i++) {
        flatidx += idx[i] * pdvec[i];
    }
    
    return flatidx;
}

};

#endif /* tensor_hpp */
