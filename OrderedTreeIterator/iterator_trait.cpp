#pragma once

namespace nonstd
{

ptrdiff_t compare_(int data1, int data2)
{
    return data1 - data2;
}

ptrdiff_t compare_(const std::string& data1, const std::string& data2)
{
    return data1.compare(data2);
}

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
ptrdiff_t iterator_trait<_T, _D>::compare(const _D& data1, const _D& data2) const
{
    return compare_(data1, data2);
}

template <typename _T, typename _D>
ptrdiff_t iterator_trait<_T, _D>::compare(const node<_D>* node1, const node<_D>* node2) const
{
    if (node1 != nullptr && node2 != nullptr)
    {
        return compare(node1->get_data(), node2->get_data());
    }
    else 
    {
        return node1 - node2;
    }
}

template <typename _T, typename _D>
ptrdiff_t iterator_trait<_T, _D>::compare(const node_ptr<_D>& ptr1, const node_ptr<_D>& ptr2) const
{
    return compare(ptr1.get(), ptr2.get());
}

template <typename _T, typename _D>
ptrdiff_t iterator_trait<_T, _D>::compare(const node_wptr<_D>& wptr1, const node_wptr<_D>& wptr2) const
{
    return compare(wptr1.lock(), wptr2.lock());
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
            return compare(data1, data2);
        }
    }
    else
    {
        return compare(node1, node2);
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
    assert (ptr);

    auto iter = m_visited.find(ptr);
    if (iter != m_visited.end()) 
    {
        return;
    }
    m_visited.insert(ptr);

    auto node = ptr.get();
    assert (node);

    // stack reverses the order to pop first element, since the last element needs to be inserted first
    // queue stays in order
    if constexpr(std::is_same<_T, node_stack<_D>>::value)
    {
        for (int i = node->get_children().size() - 1; i >= 0; i--) 
        {
            auto n = node->get_children()[i];
            cache_add(n);
        }
    }
    else if constexpr(std::is_same<_T, node_queue<_D>>::value)
    {
        for (int i = 0; i < node->get_children().size(); i++) 
        {
            auto n = node->get_children()[i];
            cache_add(n);
        }
    } 
    else
    {
        assert(0);
    }
    
    // Next node
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
