#include <iostream>

#include <memory>
#include <list>
#include <unordered_set>
#include <stack>
#include <queue>
#include <string>
#include <cassert>

#include "nonstd.h"

template <typename _D>
void testType()
{
    nonstd::node<_D> n;
    nonstd::tree<_D> t;
    nonstd::iterator_trait_dfs<_D> d;
    nonstd::iterator_trait_bfs<_D> b;

    // auto idb = t.begin<nonstd::iterator_trait_dfs<_D>>();
    // auto ibb = t.begin<nonstd::iterator_trait_bfs<_D>>();
    // auto ide = t.end<nonstd::iterator_trait_dfs<_D>>();
    // auto ibe = t.end<nonstd::iterator_trait_bfs<_D>>();
}

int main(int, char**) {
    testType<void*>();
    testType<std::string>();
    
    using type = std::string;
    nonstd::tree<type> t;
    
    auto idb = t.begin<nonstd::iterator_trait_dfs<type>>();
    auto ibb = t.begin<nonstd::iterator_trait_bfs<type>>();
    auto ide = t.end<nonstd::iterator_trait_dfs<type>>();
    auto ibe = t.end<nonstd::iterator_trait_bfs<type>>();
}
