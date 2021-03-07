#include <iostream>
#include <vector>
#include "rackoner.h"

void runTest(int items, int width) {
    Rackoner r(items, width);
    r.print();
    int moves = 1;
    while (r.next()) {
        moves++;
        r.print();
    }
    std::cout << "Items(" << items << ") Width(" << width << ") Moves (+1): " << moves << std::endl;
    std::cout << "----------" << std::endl;
}

int main() {
    runTest(1, 1);
    runTest(2, 2);
    runTest(3, 3);
    runTest(4, 4);
    runTest(5, 5);
    runTest(6, 6);
    runTest(7, 7);
    runTest(10, 4);
    return 0;
}
