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

    static int_coll m_dfs;
    static int_coll m_bfs;
    static int_coll m_postorder;
    static int_coll m_dfs_accum;
    static int_coll m_bfs_accum;
    static int_coll m_postorder_accum;

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

    static const int_coll& get_dfs() { return m_dfs; }
    static const int_coll& get_bfs() { return m_bfs; }
    static const int_coll& get_postorder() { return m_postorder; }
    static const int_coll& get_dfs_accum() { return m_dfs_accum; }
    static const int_coll& get_bfs_accum() { return m_bfs_accum; }
    static const int_coll& get_postorder_accum() { return m_postorder_accum; }

public: // Dump data
    void print(const std::string& header) const;
};

template <typename _D>
sample_builder<_D>::int_coll sample_builder<_D>::m_dfs {0, 1, 7, 8, 9, 17, 18, 19, 20, 2, 10, 11, 3, 12, 21, 22, 23, 4, 13, 14, 15, 24, 25, 26, 27, 28, 16, 5, 6};
template <typename _D>
sample_builder<_D>::int_coll sample_builder<_D>::m_bfs {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};
template <typename _D>
sample_builder<_D>::int_coll sample_builder<_D>::m_postorder {7, 8, 17, 18, 19, 20, 9, 1, 10, 11, 2, 21, 22, 23, 12, 3, 13, 14, 26, 27, 28, 25, 24, 15, 16, 4, 5, 6};
template <typename _D>
sample_builder<_D>::int_coll sample_builder<_D>::m_dfs_accum = {0, 1, 8, 16, 25, 42, 60, 79, 99, 101, 111, 122, 125, 137, 158, 180, 203, 207, 220, 234, 249, 273, 298, 324, 351, 379, 395, 400, 406};
template <typename _D>
sample_builder<_D>::int_coll sample_builder<_D>::m_bfs_accum = {0, 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78, 91, 105, 120, 136, 153, 171, 190, 210, 231, 253, 276, 300, 325, 351, 378, 406};
template <typename _D>
sample_builder<_D>::int_coll sample_builder<_D>::m_postorder_accum = {7, 15, 32, 50, 69, 89, 98, 99, 109, 120, 122, 143, 165, 188, 200, 203, 216, 230, 256, 283, 311, 336, 360, 375, 391, 395, 400, 406, 406};

};

#include "samples.cpp"
