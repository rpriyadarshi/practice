#include <iostream>

#include <memory>
#include <list>
#include <unordered_set>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <cassert>
#include <numeric>

#include <gtest/gtest.h>

#include "nonstd.h"
#include "unittest.h"

TEST_F(intTreeTest, build) 
{
    EXPECT_EQ(get_sample_builder().get_nodes().size(), 29);
    EXPECT_EQ(get_sample_builder().get_nodes().size(), get_sample_builder().get_node_ptrs().size());

    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[0], nullptr);

    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[1], get_sample_builder().get_node_ptrs()[0]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[2], get_sample_builder().get_node_ptrs()[0]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[3], get_sample_builder().get_node_ptrs()[0]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[4], get_sample_builder().get_node_ptrs()[0]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[5], get_sample_builder().get_node_ptrs()[0]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[6], get_sample_builder().get_node_ptrs()[0]);

    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[7], get_sample_builder().get_node_ptrs()[1]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[8], get_sample_builder().get_node_ptrs()[1]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[9], get_sample_builder().get_node_ptrs()[1]);

    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[10], get_sample_builder().get_node_ptrs()[2]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[11], get_sample_builder().get_node_ptrs()[2]);

    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[12], get_sample_builder().get_node_ptrs()[3]);

    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[13], get_sample_builder().get_node_ptrs()[4]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[14], get_sample_builder().get_node_ptrs()[4]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[15], get_sample_builder().get_node_ptrs()[4]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[16], get_sample_builder().get_node_ptrs()[4]);

    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[17], get_sample_builder().get_node_ptrs()[9]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[18], get_sample_builder().get_node_ptrs()[9]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[19], get_sample_builder().get_node_ptrs()[9]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[20], get_sample_builder().get_node_ptrs()[9]);

    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[21], get_sample_builder().get_node_ptrs()[12]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[22], get_sample_builder().get_node_ptrs()[12]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[23], get_sample_builder().get_node_ptrs()[12]);

    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[24], get_sample_builder().get_node_ptrs()[15]);

    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[25], get_sample_builder().get_node_ptrs()[24]);

    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[26], get_sample_builder().get_node_ptrs()[25]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[27], get_sample_builder().get_node_ptrs()[25]);
    EXPECT_EQ(get_sample_builder().get_parent_ptrs()[28], get_sample_builder().get_node_ptrs()[25]);
}

TEST_F(intTreeTest, seq) 
{
    for (int i = 0; i < get_sample_builder().get_nodes().size(); i++)
    {
        auto wptr = get_sample_builder().get_nodes()[i];
        auto ptr = wptr.lock();
        auto node = ptr.get();
        EXPECT_EQ(node->get_data(), i);
    }
}

TEST_F(intTreeTest, dfs)
{
    int i = 0;
    for (auto iter = get_sample_builder().get_tree().begin<nonstd::iterator_trait_dfs<int>>();
        iter != get_sample_builder().get_tree().end<nonstd::iterator_trait_dfs<int>>();
        iter++)
    {
        auto wptr = *iter;
        auto ptr = wptr.lock();
        auto node = ptr.get();
        auto val = node->get_data();
        EXPECT_EQ(val, get_sample_builder().get_dfs()[i++]);
    }
    EXPECT_EQ(i, get_sample_builder().get_nodes().size());
}

TEST_F(intTreeTest, bfs)
{
    int i = 0;
    for (auto iter = get_sample_builder().get_tree().begin<nonstd::iterator_trait_bfs<int>>();
        iter != get_sample_builder().get_tree().end<nonstd::iterator_trait_bfs<int>>();
        iter++)
    {
        auto wptr = *iter;
        auto ptr = wptr.lock();
        auto node = ptr.get();
        auto val = node->get_data();
        EXPECT_EQ(val, get_sample_builder().get_bfs()[i++]);
    }
    EXPECT_EQ(i, get_sample_builder().get_nodes().size());
}

TEST_F(intTreeTest, postorder)
{
    int i = 0;
    for (auto iter = get_sample_builder().get_tree().begin<nonstd::iterator_trait_po<int>>();
        iter != get_sample_builder().get_tree().end<nonstd::iterator_trait_po<int>>();
        iter++)
    {
        auto wptr = *iter;
        auto ptr = wptr.lock();
        auto node = ptr.get();
        auto val = node->get_data();
        EXPECT_EQ(val, get_sample_builder().get_postorder()[i++]);
    }
    EXPECT_EQ(i, get_sample_builder().get_nodes().size());
}

TEST_F(intTreeTest, dfs_accum)
{
    int i = 0;
    auto a1 = std::accumulate(
        get_sample_builder().get_tree().begin<nonstd::iterator_trait_dfs<int>>(),
        get_sample_builder().get_tree().end<nonstd::iterator_trait_dfs<int>>(),
        nonstd::tree<int>::create_node(0), // start with first element
        [&i](nonstd::node_wptr<int> a, nonstd::node_wptr<int> b) 
            {
                auto node_a = a.lock().get();
                auto node_b = b.lock().get();
                auto val = node_a->get_data() + node_b->get_data();
                EXPECT_EQ(val, nonstd::sample_builder<int>::get_dfs_accum()[i++]);
                return nonstd::tree<int>::create_node(val);
            }
    );
}

TEST_F(intTreeTest, bfs_accum)
{
    int i = 0;
    auto a1 = std::accumulate(
        get_sample_builder().get_tree().begin<nonstd::iterator_trait_bfs<int>>(),
        get_sample_builder().get_tree().end<nonstd::iterator_trait_bfs<int>>(),
        nonstd::tree<int>::create_node(0), // start with first element
        [&i](nonstd::node_wptr<int> a, nonstd::node_wptr<int> b) 
            {
                auto node_a = a.lock().get();
                auto node_b = b.lock().get();
                auto val = node_a->get_data() + node_b->get_data();
                EXPECT_EQ(val, nonstd::sample_builder<int>::get_bfs_accum()[i++]);
                return nonstd::tree<int>::create_node(val);
            }
    );
}

TEST_F(intTreeTest, postorder_accum)
{
    int i = 0;
    auto a1 = std::accumulate(
        get_sample_builder().get_tree().begin<nonstd::iterator_trait_po<int>>(),
        get_sample_builder().get_tree().end<nonstd::iterator_trait_po<int>>(),
        nonstd::tree<int>::create_node(0), // start with first element
        [&i](nonstd::node_wptr<int> a, nonstd::node_wptr<int> b) 
            {
                auto node_a = a.lock().get();
                auto node_b = b.lock().get();
                auto val = node_a->get_data() + node_b->get_data();
                EXPECT_EQ(val, nonstd::sample_builder<int>::get_postorder_accum()[i++]);
                return nonstd::tree<int>::create_node(val);
            }
    );
}

TEST(NonStd, BasicClasses) {
    using type = int;

    nonstd::node<type> n;
    nonstd::tree<type> t;
    nonstd::iterator_trait_dfs<type> d;
    nonstd::iterator_trait_bfs<type> b;
}

TEST(NonStd, BasicIterators) {
    using type = std::string;
    // using type = int;

    nonstd::tree<type> t;
    
    auto idb = t.begin<nonstd::iterator_trait_dfs<type>>();
    auto ide = t.end<nonstd::iterator_trait_dfs<type>>();
    EXPECT_TRUE(idb == ide);

    auto ibb = t.begin<nonstd::iterator_trait_bfs<type>>();
    auto ibe = t.end<nonstd::iterator_trait_bfs<type>>();
    EXPECT_TRUE(ibb == ibe);
}
