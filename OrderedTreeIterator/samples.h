#pragma once

namespace nonstd
{

void init(int& data)
{
    data = 0;
}

int& incr(int& data)
{
    return ++data;
}

template <typename _D>
class sample_builder
{
public: // Using, typedefs etc.
    using node_coll = std::vector<nonstd::node_wptr<_D>>;
    using node_ptr_coll = std::vector<nonstd::node<_D>*>;
    using int_coll = std::vector<int>;

private: // Class data
    nonstd::tree<_D> m_tree;
    node_coll m_nodes;
    node_ptr_coll m_node_ptrs;
    node_ptr_coll m_parent_ptrs;
    int_coll m_dfs {0, 1, 7, 8, 9, 17, 18, 19, 20, 2, 10, 11, 3, 12, 21, 22, 23, 4, 13, 14, 15, 24, 25, 26, 27, 28, 16, 5, 6};
    int_coll m_bfs {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};

public: // Constructors, destructors
    sample_builder() {}
    ~sample_builder() {}

public: // Builders
    void build();

public: // Accessors
    const nonstd::tree<_D>& get_tree() const { return m_tree; }
    nonstd::tree<_D>& get_tree() { return m_tree; }

    const node_coll& get_nodes() const { return m_nodes; }
    node_coll& get_nodes() { return m_nodes; }

    const node_ptr_coll& get_parent_ptrs() const { return m_parent_ptrs; }
    node_ptr_coll& get_parent_ptrs() { return m_parent_ptrs; }

    const node_ptr_coll& get_node_ptrs() const { return m_node_ptrs; }
    node_ptr_coll& get_node_ptrs() { return m_node_ptrs; }

    const int_coll& get_dfs() const { return m_dfs; }
    const int_coll& get_bfs() const { return m_bfs; }

public: // Dump data
    void print(const std::string& header) const;
};

};

#include "samples.cpp"
