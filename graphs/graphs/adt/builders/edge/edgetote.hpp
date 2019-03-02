//
//  sample.hpp
//  graphs
//
//  Created by Rohit Priyadarshi on 2/25/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#ifndef edgetote_h
#define edgetote_h

////////////////////////////////////////////////////////////////////////////////
namespace adt {

////////////////////////////////////////////////////////////////////////////////
class tote {
public:
    tote() : m_data(0) {}
    ~tote() {}
    
public: // Utility functions
    void dump(std::ostream& o) const;
    
public: // Accessors
    int data() const { return m_data; }
    
public: // Accessors
    int data() { return m_data; }
    void data(int d) { m_data = d; }

private:
    int m_data;
};

////////////////////////////////////////////////////////////////////////////////
class vertexTote : public tote {
public:
    vertexTote() : tote() {}
    ~vertexTote() {}
};

////////////////////////////////////////////////////////////////////////////////
class edgeTote : public tote {
public:
    edgeTote() : tote() {}
    ~edgeTote() {}
};

////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<< (std::ostream& o, const tote& t) {
    t.dump(o);
    return o;
}

////////////////////////////////////////////////////////////////////////////////
void tote::dump(std::ostream& o) const {
    o << data();
}

};

#endif /* edgetote_h */
