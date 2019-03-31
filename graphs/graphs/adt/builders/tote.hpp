//
//  sample.hpp
//  graphs
//
//  Created by Rohit Priyadarshi on 2/25/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#ifndef tote_hpp
#define tote_hpp

////////////////////////////////////////////////////////////////////////////////
namespace adt {

////////////////////////////////////////////////////////////////////////////////
class tote {
public:
    tote() : m_flags(0), m_data(0) {}
    ~tote() {}
    
public: // Utility functions
    void dump(std::ostream& o) const;
    
public: // Accessors
    int flags() const { return m_flags; }
    int data() const { return m_data; }

public: // Accessors
    int data() { return m_data; }
    void flags(int f) const { m_flags = f; }
    void data(int d) { m_data = d; }

private:
    mutable int m_flags;
    int m_data;
};

////////////////////////////////////////////////////////////////////////////////
class vertexTote : public tote {
public:
    vertexTote() : tote(), m_cache(0) {}
    ~vertexTote() {}
    
public: // Accessors
    int cache() const { return m_cache; }

public: // Accessors
    int cache() { return m_cache; }
    void cache(int c) { m_cache = c; }

private:
    int m_cache;
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

#endif /* tote_hpp */
