#include <iostream>

#include <memory>
#include <list>
#include <unordered_set>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <cassert>

#include "nonstd.h"

int main(int argc, const char* argv[])
{
    nonstd::sample_builder<int> sample_builder;
    sample_builder.build();
    sample_builder.print("dump");

    for (auto iter = sample_builder.get_tree().begin<nonstd::iterator_trait_dfs<int>>();
        iter != sample_builder.get_tree().end<nonstd::iterator_trait_dfs<int>>();
        iter++)
    {
        auto wptr = *iter;
        auto ptr = wptr.lock();
        auto node = ptr.get();
        node->print("dfs", 0, true);        
    }

    for (auto iter = sample_builder.get_tree().begin<nonstd::iterator_trait_bfs<int>>();
        iter != sample_builder.get_tree().end<nonstd::iterator_trait_bfs<int>>();
        iter++)
    {
        auto wptr = *iter;
        auto ptr = wptr.lock();
        auto node = ptr.get();
        node->print("bfs", 0, true);        
    }

    for (auto iter = sample_builder.get_tree().begin<nonstd::iterator_trait_po<int>>();
        iter != sample_builder.get_tree().end<nonstd::iterator_trait_po<int>>();
        iter++)
    {
        auto wptr = *iter;
        auto ptr = wptr.lock();
        auto node = ptr.get();
        node->print("postorder", 0, true);        
    }
    return 0;
}
