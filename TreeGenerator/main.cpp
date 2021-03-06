#include <iostream>
#include <vector>
#include "rackoner.h"

int main() {
    Rackoner r(4, 10);
    int moves = 0;
    while (r.moveOnce()) {
        moves++;
        r.print();
    }
    std::cout << "Moves: " << moves << std::endl;
    return 0;
}
