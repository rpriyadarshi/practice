#include <iostream>
#include <vector>

#include "rackoner.h"
#include "schema.h"
#include "generator.h"

void runTestSingle(int items, int width, int expected) {
    Generator g(items, width);
    g.solve(0, width, items);
    int moves = g.getCount();
    std::cout << "Items(" << items << ") Width(" << width << ") Moves (+1): " << moves << std::endl;
    if (moves != expected) {
        std::cout << "ERROR: Move mismatch occured! (" << moves << " != " << expected << ")" << std::endl;
    }
    std::cout << "----------" << std::endl;
}

void runTestFull(int items, int width, int expected) {
    Generator g(items, width);
    g.solve();
    int moves = g.getCount();
    std::cout << "Items(" << items << ") Width(" << width << ") Moves: " << moves << std::endl;
    if (moves != expected) {
        std::cout << "ERROR: Move mismatch occured! (" << moves << " != " << expected << ")" << std::endl;
    }
    std::cout << "----------" << std::endl;
}

int main() {
    runTestSingle(1, 1, 1);
    runTestSingle(2, 2, 2);
    runTestSingle(3, 3, 3);
    runTestSingle(4, 4, 5);
    runTestSingle(5, 5, 7);
    runTestSingle(6, 6, 11);
    runTestSingle(7, 7, 15);
    runTestSingle(10, 4, 20);

    runTestSingle(2, 2, 2);
    runTestSingle(3, 3, 3);

    runTestFull(4, 3, 4);
    runTestFull(7, 2, 10);
    runTestFull(8, 5, 35);
//    runTestFull(30, 3, 10);
    return 0;
}
