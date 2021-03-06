#include <iostream>
#include <vector>
#include "rackoner.h"

int main() {
    Rackoner r(4, 10);
    while (r.moveOnce()) {
        r.print();
    }
    return 0;
}
