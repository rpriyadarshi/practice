#pragma once

namespace nonstd
{

template <typename _D>
class tree
{
public: // Using, typedefs etc.

private: // Class data
    node<_D> m_root;

public: // Constructors, destructors
    tree() {}
    ~tree() {}

public: // Accessors
    const node_wptr<_D> get_root() const { return m_root; }
    node_wptr<_D> get_root() { return m_root; }

public: // Helpers
    template <typename _T>
    iterator<_T, _D> begin();
    template <typename _T>
    iterator<_T, _D> end();

private: // Creation and destruction
    node_wptr<_D> create_root();
    static node_ptr<_D> create_node();
    static node_ptr<_D> create_node(node_wptr<_D> parent, _D data);
    static void destroy(node_rptr<_D> node);

public: // Dump data
    void print(const std::string& header, bool shallow) const;
};

};

#include "tree.cpp"
