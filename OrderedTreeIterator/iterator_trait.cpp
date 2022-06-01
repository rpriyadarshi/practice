#pragma once

namespace nonstd
{

template <typename _T, typename _D>
node_ptr<_D> iterator_trait<_T, _D>::m_end_node;

template <typename _T, typename _D>
node_wptr<_D> iterator_trait<_T, _D>::cache_top()
{
    if constexpr(std::is_same<_T, node_stack<_D>>::value)
    {
        return m_cache.top();
    }
    else if constexpr(std::is_same<_T, node_queue<_D>>::value)
    {
        return m_cache.front();
    } 
    else
    {
        assert(0);
        return node_wptr<_D>();
    }
}

template <typename _T, typename _D>
bool iterator_trait<_T, _D>::is_end() const
{
    auto ptr1 = m_curr_node.lock();
    auto node1 = ptr1.get();
    auto node2 = m_end_node.get();

    return node1 == node2;
}

template <typename _T, typename _D>
void iterator_trait<_T, _D>::set_end()
{
    m_curr_node = m_end_node;
}

template <typename _T, typename _D>
ptrdiff_t iterator_trait<_T, _D>::compare(const iterator_trait& iter) const
{
    auto ptr1 = m_curr_node.lock();
    auto ptr2 = iter.m_curr_node.lock();
    auto node1 = ptr1.get();
    auto node2 = ptr2.get();
    if (node1 == node2) 
    {
        return 0;
    }
    else if (node1 && node2) 
    {
        auto data1 = node1->get_data();
        auto data2 = node2->get_data();
        if (data1 == data2)
        {
            return 0;
        }
        else
        {
            return data1 - data2;
        }
    }
    else
    {
        return node1 - node2;
    }
}

template <typename _T, typename _D>
void iterator_trait<_T, _D>::forward()
{
    if (is_end())
    {
        return;
    }

    auto wptr = cache_top();
    cache_pop();

    auto ptr = wptr.lock();
    if (!ptr)
    {
        return;
    }

    auto iter = m_visited.find(ptr);
    if (iter != m_visited.end()) 
    {
        return;
    }
    m_visited.insert(ptr);

    auto node = ptr.get();
    if (!node) 
    {
        return;
    }

    for (auto node : node->get_children()) 
    {
        cache_add(node);
    }

    if (cache_empty()) 
    {
        set_end();
    }
    else
    {
        m_curr_node = cache_top();
    }
}

template <typename _T, typename _D>
void iterator_trait<_T, _D>::backward()
{
}

};
