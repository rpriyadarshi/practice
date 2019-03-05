//
//  runfunc.hpp
//  n-dimensional-tensor
//
//  Created by Rohit Priyadarshi on 3/3/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#ifndef runfunc_hpp
#define runfunc_hpp

namespace nten {

////////////////////////////////////////////////////////////////////////////////
class runfunc {
public: // Constructors/destructors
    runfunc(const UIntVec& vec);
    ~runfunc();
    
public: // Utility
    unsigned int index(const UIntVec& idx) const;
    void dump(std::ostream& o, const UIntVec& idx) const;

public: // Operators
    unsigned int operator()(const UIntVec& idx);
    
public: // Accessors
    const UIntVec& pdVec() const { return m_pdVec; }

protected: // Accessors
    
private:
    const UIntVec& m_pdVec;
};

////////////////////////////////////////////////////////////////////////////////
inline runfunc::runfunc(const UIntVec& vec)
    : m_pdVec(vec) {
}

inline runfunc::~runfunc() {
}

inline unsigned int runfunc::index(const UIntVec& idx) const {
    const UIntVec& pdvec = pdVec();
    unsigned int flatidx = 0;
    for (int i = 0; i < idx.size(); i++) {
        flatidx += idx[i] * pdvec[i];
    }
    
    return flatidx;
}

inline void runfunc::dump(std::ostream& o, const UIntVec& idx) const {
    std::cout << index(idx) << ": ";
    for (auto id: idx) {
        o << id << " ";
    }
    o << std::endl;
}

inline unsigned int runfunc::operator()(const UIntVec& idx) {
    dump(std::cout, idx);
    return index(idx);
}

};

#endif /* runfunc_hpp */
