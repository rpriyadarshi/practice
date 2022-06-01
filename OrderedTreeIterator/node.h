#pragma once

namespace nonstd
{

template <typename _D>
class node
{
public: // Using, typedefs etc.
    using node_ptr = std::shared_ptr<node>;
    using node_wptr = std::weak_ptr<node>;
    using node_coll = std::list<node_ptr>;

private: // Class data
    node_wptr m_parent;
    node_coll m_children;
    _D m_data;

public: // Constructors, destructors
    node() {}
    node(node_wptr parent, _D data) : m_parent(parent), m_data(data) {}
    ~node() {}

public: // Accessors
    const node_wptr get_parent() const { return m_parent; }
    node_wptr get_parent() { return m_parent; }
    void set_parent(const node_wptr parent) { m_parent = parent; }

    const node_coll& get_children() const { return m_children; }
    node_coll& get_children() { return m_children; }

    const _D& get_data() const { return m_data; }
    _D& get_data() { return m_data; }

public: // Dump data
    void print(const std::string& header, size_t indent, bool shallow) const;
};

template <typename _D>
using node_rptr = node<_D>*;
template <typename _D>
using node_ptr = std::shared_ptr<node<_D>>;
template <typename _D>
using node_wptr = std::weak_ptr<node<_D>>;

};

#include "node.cpp"
