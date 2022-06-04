#pragma once

namespace nonstd
{
//
//             0
//             |
//   __________+________________________
//   [1        2        3         4 5 6]
//    |        |        |         |
// ___+___   ___+___   _+__  _____+_______
// [7 8 9]   [10 11]   [12]  [13 14 15 16]
//       |              |           |
// ______+______    ____+_____     _+__
// [17 18 19 20]    [21 22 23]     [24]
//                                  |
//                                 _+__
//                                 [25]
//                                  |
//                              ____+_____
//                              [26 27 28]
//
template <typename _D>
void sample_builder<_D>::build()
{
    _D data;
    init(data);
    m_nodes.push_back(m_tree.create_root(data));

    m_nodes.push_back(m_tree.create_node(m_nodes[0], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[0], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[0], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[0], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[0], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[0], incr(data)));

    m_nodes.push_back(m_tree.create_node(m_nodes[1], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[1], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[1], incr(data)));

    m_nodes.push_back(m_tree.create_node(m_nodes[2], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[2], incr(data)));

    m_nodes.push_back(m_tree.create_node(m_nodes[3], incr(data)));

    m_nodes.push_back(m_tree.create_node(m_nodes[4], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[4], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[4], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[4], incr(data)));

    m_nodes.push_back(m_tree.create_node(m_nodes[9], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[9], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[9], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[9], incr(data)));

    m_nodes.push_back(m_tree.create_node(m_nodes[12], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[12], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[12], incr(data)));

    m_nodes.push_back(m_tree.create_node(m_nodes[15], incr(data)));

    m_nodes.push_back(m_tree.create_node(m_nodes[24], incr(data)));

    m_nodes.push_back(m_tree.create_node(m_nodes[25], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[25], incr(data)));
    m_nodes.push_back(m_tree.create_node(m_nodes[25], incr(data)));

    for (auto wptr : m_nodes)
    {
        auto ptr = wptr.lock();
        auto node = ptr.get();
        m_node_ptrs.push_back(node);

        auto pwptr = node->get_parent();
        auto pptr = pwptr.lock();
        auto pnode = pptr.get();
        m_parent_ptrs.push_back(pnode);
    }
}

template <typename _D>
void sample_builder<_D>::print(const std::string& header) const
{
    m_tree.print(header);
}

};
