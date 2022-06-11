#pragma once

namespace nonstd
{

template <typename _T, typename _D>
class iterator_trait
{
public: // Using, typedefs etc.
    using node_set = std::unordered_set<node_ptr<_D>>;
    using reference = node_wptr<_D>;

protected: // Class data
    _T m_cache;
    node_set m_visited;
    node_wptr<_D> m_curr_node;
    static node_ptr<_D> m_end_node;

public: // Constructors, destructors
    iterator_trait() 
        : m_curr_node(m_end_node) { cache_add(m_curr_node); }
    explicit iterator_trait(const node_wptr<_D> node) 
        : m_curr_node(node) { cache_add(m_curr_node); }
    iterator_trait(const iterator_trait& trait) 
        : m_curr_node(trait.m_end_node) { cache_add(m_curr_node); }
    ~iterator_trait() {}

public: // Helpers
    bool is_end() const;
    void set_end();

    void cache_add(const node_wptr<_D> node) { m_cache.push(node); }
    node_wptr<_D> cache_top();
    void cache_pop() { m_cache.pop(); }
    bool cache_empty() const { return m_cache.empty(); }

    ptrdiff_t compare(const iterator_trait& trait) const;

    reference get_value() const { return m_curr_node; }

public: // Algorithms
    void forward();
    void backward();

private: // Helpers
    ptrdiff_t compare(const _D& data1, const _D& data2) const;
    ptrdiff_t compare(const node<_D>* node1, const node<_D>* node2) const;
    ptrdiff_t compare(const node_ptr<_D>& ptr1, const node_ptr<_D>& ptr2) const;
    ptrdiff_t compare(const node_wptr<_D>& wptr1, const node_wptr<_D>& wptr2) const;
    
public: // Dump data
};

template <typename _D>
using node_stack = std::stack<node_wptr<_D>>;
template <typename _D>
using node_queue = std::queue<node_wptr<_D>>;

template <typename _D>
using iterator_trait_dfs = iterator_trait<node_stack<_D>, _D>;
template <typename _D>
using iterator_trait_bfs = iterator_trait<node_queue<_D>, _D>;

};

#include "iterator_trait.cpp"
