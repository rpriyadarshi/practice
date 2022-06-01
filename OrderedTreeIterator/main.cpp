#include <iostream>

#include <memory>
#include <list>
#include <unordered_set>
#include <stack>
#include <queue>
#include <string>
#include <cassert>

#include "nonstd.h"

int main(int, char**) {
    nonstd::node<void*> n;
    nonstd::tree<void*> t;
    nonstd::iterator_trait_dfs<void*> d;
    nonstd::iterator_trait_bfs<void*> b;
}
