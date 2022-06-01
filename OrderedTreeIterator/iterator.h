#pragma once

namespace nonstd
{

template <typename _T, typename _D>
class iterator
{
public: // Using, typedefs etc.
    using reference = node_wptr<_D>;

private: // Class data
    _T m_trait;

public: // Constructors, destructors
    iterator() {}
    explicit iterator(node_wptr<_D> node) : m_trait(node) {}
    iterator(const iterator& iter) : m_trait(iter.m_trait) {}
    ~iterator() {}

public: // Helpers
    iterator& operator=(const iterator& iter) { if (this != &iter) { m_trait = iter.m_trait; } return *this; }
    bool operator==(const iterator& iter) const { return m_trait.compare(iter.m_trait) == 0; }
    bool operator!=(const iterator& iter) const { return m_trait.compare(iter.m_trait) != 0; }
    iterator& operator++() { m_trait.forward(); return *this; }
    iterator& operator--() { m_trait.backeard(); return *this; }
    iterator& operator++(int) { m_trait.forward(); return *this; }
    iterator& operator--(int) { m_trait.backeard(); return *this; }
    reference operator*() const { return m_trait.get_value(); }

public: // Dump data

};

};

#include "iterator.cpp"
