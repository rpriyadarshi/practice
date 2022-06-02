#include <iostream>

#include <memory>
#include <list>
#include <unordered_set>
#include <stack>
#include <queue>
#include <string>
#include <cassert>
// #include <format>
#include <gtest/gtest.h>

#include "nonstd.h"

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

