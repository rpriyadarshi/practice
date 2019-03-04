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

using ExtentVec = std::vector<unsigned int>;
using IndexVec = std::vector<unsigned int>;

class tensor {
public: // Constructors/destructors
    tensor(const float* data, const ExtentVec& evec);
    ~tensor();
    
public: // Utility
    void indexTree(IndexVec& idx);
    void indexTree(IndexVec& idx, unsigned int loc);
    void callIndex(IndexVec& idx, unsigned int loc);
    
public: // Accessors
    const float* data() { return m_data; }
    const ExtentVec& evec() const { return m_evec; }

protected: // Accessors

private:
    const float* m_data;
    const ExtentVec& m_evec;
};

inline tensor::tensor(const float* data, const ExtentVec& evec)
    : m_data(data), m_evec(evec) {
}

inline tensor::~tensor() {
}

inline void tensor::indexTree(IndexVec& idx) {
    indexTree(idx, 0);
}

inline void tensor::indexTree(IndexVec& idx, unsigned int loc) {
    int ext = evec()[loc];
    for (int i = 0; i < ext; i++) {
        idx[loc] = i;
        callIndex(idx, loc);
        int nextloc = loc + 1;
        if (nextloc < evec().size()) {
            indexTree(idx, nextloc);
        }
    }
};

inline void tensor::callIndex(IndexVec& idx, unsigned int loc) {
    if (loc != evec().size() - 1) {
        return;
    }
    for (auto id: idx) {
        std::cout << id << " ";
    }
    std::cout << std::endl;
}

};

#endif /* tensor_hpp */
