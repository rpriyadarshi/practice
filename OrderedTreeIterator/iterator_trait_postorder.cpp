#pragma once

namespace nonstd
{

template <typename _T, typename _D>
void iterator_trait_postorder<_T, _D>::print_cache()
{
    std::cout << "[";
    for (auto dump = iterator_trait<_T, _D>::m_cache; !dump.empty(); dump.pop())
    {
        std::cout << dump.top().lock().get()->get_data() << " ";
    }
    std::cout << "]" << std::endl;
}

template <typename _T, typename _D>
void iterator_trait_postorder<_T, _D>::next_valid()
{
    bool expand = false;
    do
    {
        if (iterator_trait<_T, _D>::cache_empty()) 
        {
            continue;
        }
        auto wptr = iterator_trait<_T, _D>::cache_top();

        auto ptr = wptr.lock();
        assert (ptr);

        auto iter = iterator_trait<_T, _D>::m_visited.find(ptr);
        if (iter != iterator_trait<_T, _D>::m_visited.end()) 
        {
            continue;
        }
        iterator_trait<_T, _D>::m_visited.insert(ptr);

        auto node = ptr.get();
        assert (node);

        expand = false;
        if (node->get_children().size()) 
        {
            auto iter2 = m_expanded.find(ptr);
            if (iter2 == m_expanded.end()) 
            {
                m_expanded.insert(ptr);
                expand = true;
            }
        }

        if (expand)
        {
            for (int i = node->get_children().size() - 1; i >= 0; i--) 
            {
                auto n = node->get_children()[i];
                iterator_trait<_T, _D>::cache_add(n);
            }
        }
        // print_cache();
    }
    while (expand);
}

template <typename _T, typename _D>
void iterator_trait_postorder<_T, _D>::forward()
{
    if (iterator_trait<_T, _D>::is_end())
    {
        return;
    }

    next_valid();

    // Next node
    if (iterator_trait<_T, _D>::cache_empty()) 
    {
        iterator_trait<_T, _D>::set_end();
    }
    else
    {
        iterator_trait<_T, _D>::m_curr_node = iterator_trait<_T, _D>::cache_top();
        iterator_trait<_T, _D>::cache_pop();
    }
}

template <typename _T, typename _D>
void iterator_trait_postorder<_T, _D>::backward()
{
}

};
