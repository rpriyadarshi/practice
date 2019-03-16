//
//  testers.hpp
//  graphs
//
//  Created by Rohit Priyadarshi on 3/15/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#ifndef testers_hpp
#define testers_hpp

////////////////////////////////////////////////////////////////////////////////
namespace adt {
    
////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
class testers {
public: // Constructors/destructors
    testers();
    ~testers();
    
public: // Builders
    void bldedge(const std::string& filename);
    
public: // Tester
    void runbelf();
    void runflw();

public: // Accessors
    const factory& fac() const { return m_fac; }
    const graph<DV, DE>& gr() const { return m_gr; }
    const builder<DV, DE>& bld() const { return m_bld; }
    const bellmanford<DV, DE>& belf() const { return m_belf; }
    const floydwarshall<DV, DE>& flw() const { return m_flw; }

protected: // Accessors
    factory& fac() { return m_fac; }
    graph<DV, DE>& gr() { return m_gr; }
    builder<DV, DE>& bld() { return m_bld; }
    bellmanford<DV, DE>& belf() { return m_belf; }
    floydwarshall<DV, DE>& flw() { return m_flw; }

private:
    factory m_fac;
    graph<DV, DE> m_gr;
    builder<DV, DE> m_bld;
    bellmanford<DV, DE> m_belf;
    floydwarshall<DV, DE> m_flw;
};

////////////////////////////////////////////////////////////////////////////////
template <typename DV, typename DE>
testers<DV, DE>::testers() : m_bld(m_gr), m_belf(m_gr), m_flw(m_gr) {
}

template <typename DV, typename DE>
testers<DV, DE>::~testers() {
}

template <typename DV, typename DE>
void testers<DV, DE>::bldedge(const std::string& filename) {
    bld().read(filename, fac());
//    std::cout << gr() << std::endl;
}

template <typename DV, typename DE>
void testers<DV, DE>::runbelf() {
    belf()();
    std::cout << "BF: " << belf() << std::endl;
}

template <typename DV, typename DE>
void testers<DV, DE>::runflw() {
    flw()();
    std::cout << "FW: " << flw() << std::endl;
}

};

#endif /* testers_hpp */
