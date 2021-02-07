#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

#include "satinstance.h"

int main(int argc, const char** argv) {
    SATInstance si;
    si.from_file(argv[1]);

    si.print();
    return 0;
}
