#pragma once

namespace nonstd
{
template <typename _T, typename _D>
class iterator_trait_postorder : public iterator_trait<_T, _D>
{
public: // Using, typedefs etc.
    using node_set = std::unordered_set<node_ptr<_D>>;
    using reference = node_wptr<_D>;

private: // Class data
    node_set m_expanded;

public: // Constructors, destructors
    iterator_trait_postorder() 
        : iterator_trait<_T, _D>() { forward(); }
    explicit iterator_trait_postorder(const node_wptr<_D> node) 
        : iterator_trait<_T, _D>(node) { forward(); }
    iterator_trait_postorder(const iterator_trait_postorder& trait) 
        : iterator_trait<_T, _D>(trait) { forward(); }
    ~iterator_trait_postorder() {}

public: // Helpers
    void next_valid();

public: // Algorithms
    void forward();
    void backward();
    
private: // Helpers

public: // Dump data
    void print_cache();
};

template <typename _D>
using iterator_trait_po = iterator_trait_postorder<node_stack<_D>, _D>;

};

#include "iterator_trait_postorder.cpp"
