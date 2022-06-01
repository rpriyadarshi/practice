#pragma once

namespace nonstd
{

template <typename _D>
node_wptr<_D> tree<_D>::create_root()
{
    if (!m_root.use_count())
    {
        m_root = create_node();
    }
    return m_root;
}

template <typename _D>
node_ptr<_D> tree<_D>::create_node()
{
    return node_ptr<_D>(new node<_D>(), destroy);
}

template <typename _D>
node_ptr<_D> tree<_D>::create_node(node_wptr<_D> parent, _D data)
{
    auto ptr = node_ptr<_D>(new node<_D>(parent, data), destroy);
    auto pptr = parent.lock();
    if (pptr.use_count())
    {
        auto& children = pptr.get_children();
        children.push_back(ptr);
    }
    return ptr;
}

template <typename _D>
void tree<_D>::destroy(node_rptr<_D> node)
{
    delete node;
}

};
