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

#include "nonstd.h"

int main(int argc, const char* argv[])
{
    nonstd::sample_builder<int> sample_builder;
    sample_builder.build();
    sample_builder.print("dump");

    std::cout << "dfs        {";
    for (auto iter = sample_builder.get_tree().begin<nonstd::iterator_trait_dfs<int>>();
        iter != sample_builder.get_tree().end<nonstd::iterator_trait_dfs<int>>();
        iter++)
    {
        auto wptr = *iter;
        auto ptr = wptr.lock();
        auto node = ptr.get();
        node->print(", ", 0, true);        
    }
    std::cout << "}" << std::endl;
    std::cout << "accumulate {";
    auto a1 = std::accumulate(
        sample_builder.get_tree().begin<nonstd::iterator_trait_dfs<int>>(),
        sample_builder.get_tree().end<nonstd::iterator_trait_dfs<int>>(),
        nonstd::tree<int>::create_node(0), // start with first element
        [](nonstd::node_wptr<int> a, nonstd::node_wptr<int> b) 
            {
                auto node_a = a.lock().get();
                auto node_b = b.lock().get();
                int sum = node_a->get_data() + node_b->get_data();
                std::cout << ", " << sum;
                return nonstd::tree<int>::create_node(sum);
            }
    );
    std::cout << "}" << std::endl;

    std::cout << "bfs        {";
    for (auto iter = sample_builder.get_tree().begin<nonstd::iterator_trait_bfs<int>>();
        iter != sample_builder.get_tree().end<nonstd::iterator_trait_bfs<int>>();
        iter++)
    {
        auto wptr = *iter;
        auto ptr = wptr.lock();
        auto node = ptr.get();
        node->print(", ", 0, true);        
    }
    std::cout << "}" << std::endl;
    std::cout << "accumulate {";
    auto a2 = std::accumulate(
        sample_builder.get_tree().begin<nonstd::iterator_trait_bfs<int>>(),
        sample_builder.get_tree().end<nonstd::iterator_trait_bfs<int>>(),
        nonstd::tree<int>::create_node(0), // start with first element
        [](nonstd::node_wptr<int> a, nonstd::node_wptr<int> b) 
            {
                auto node_a = a.lock().get();
                auto node_b = b.lock().get();
                int sum = node_a->get_data() + node_b->get_data();
                std::cout << ", " << sum;
                return nonstd::tree<int>::create_node(sum);
            }
    );
    std::cout << "}" << std::endl;

    std::cout << "postorder  {";
    for (auto iter = sample_builder.get_tree().begin<nonstd::iterator_trait_po<int>>();
        iter != sample_builder.get_tree().end<nonstd::iterator_trait_po<int>>();
        iter++)
    {
        auto wptr = *iter;
        auto ptr = wptr.lock();
        auto node = ptr.get();
        node->print(", ", 0, true);        
    }
    std::cout << "}" << std::endl;

    std::cout << "accumulate {";
    auto a3 = std::accumulate(
        sample_builder.get_tree().begin<nonstd::iterator_trait_po<int>>(),
        sample_builder.get_tree().end<nonstd::iterator_trait_po<int>>(),
        nonstd::tree<int>::create_node(0), // start with first element
        [](nonstd::node_wptr<int> a, nonstd::node_wptr<int> b) 
            {
                auto node_a = a.lock().get();
                auto node_b = b.lock().get();
                int sum = node_a->get_data() + node_b->get_data();
                std::cout << ", " << sum;
                return nonstd::tree<int>::create_node(sum);
            }
    );
    std::cout << "}" << std::endl;

    return 0;
}
