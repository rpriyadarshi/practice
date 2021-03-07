#include <iostream>
#include <vector>

#include "rackoner.h"
#include "schema.h"

void runTest(int items, int width, int expected) {
    Rackoner r(items, width);
    Schema s0(0, width, items, r.getSpan());
//    r.print();
    s0.print();
    int moves = 1;
    while (r.next()) {
        Schema s(0, width, items, r.getSpan());
//        r.print();
        s.print();
        moves++;
    }
    std::cout << "Items(" << items << ") Width(" << width << ") Moves (+1): " << moves << std::endl;
    if (moves != expected) {
        std::cout << "ERROR: Move mismatch occured! (" << moves << " != " << expected << ")" << std::endl;
    }
    std::cout << "----------" << std::endl;
}

int main() {
    runTest(1, 1, 1);
    runTest(2, 2, 2);
    runTest(3, 3, 3);
    runTest(4, 4, 5);
    runTest(5, 5, 7);
    runTest(6, 6, 11);
    runTest(7, 7, 15);
    runTest(10, 4, 20);
    return 0;
}
