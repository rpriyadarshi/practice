#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <deque>

#include "satinstance.h"
#include "solvers/watchlist.h"
#include "solvers/sat_base.h"
#include "solvers/recursive_sat.h"
#include "sat.h"

int main(int argc, const char** argv) {
    SATInstance si;
    si.from_file(argv[1]);

    si.print();
    return 0;
}
