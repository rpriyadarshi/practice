#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <algorithm>

#include "oddevenjump.h"

using IntVec = std::vector<int>;
using IntTable = std::vector<IntVec>;

// https://www.techiedelight.com/remove-certain-characters-string-cpp/
void loadInput(int argc, const char** argv, IntTable& table) {
    std::string filename(argv[1]);
    std::string chars("[ ]");

    std::ifstream ifstr(filename);
    std::string line;
    while (std::getline(ifstr, line)) {
        line.erase(remove_if(line.begin(), line.end(),
                          [&chars](const char& c) {
                              return chars.find(c) != std::string::npos;
                          }),
                   line.end());

        std::istringstream sstr(line);
        std::string token;
        IntVec prob;
        while (std::getline(sstr, token, ',')) {
            prob.push_back(std::stoi(token));
        }
        table.emplace_back(prob);
    }
}

void loadOutput(int argc, const char** argv, IntVec& out) {
    std::string filename(argv[2]);

    int token;
    std::ifstream ifstr(filename);
    while (ifstr.good()) {
        ifstr >> token;
        out.push_back(token);
    }
}

int main(int argc, const char** argv) {
    IntTable table;
    loadInput(argc, argv, table);
    IntVec out;
    loadOutput(argc, argv, out);

    for (int i = 0; i < table.size(); i++) {
        auto& prob = table[i];
        Solution sol;
        int rc = sol.oddEvenJumps(prob);
        std::cout << rc << " -> ";
        std::cout << "[";
        for (auto& p : prob) {
            std::cout << p << " ";
        }
        std::cout << "]";
        if (rc != out[i]) {
             std::cout << " [ != " << out[i] << "]";
        }
        std::cout << std::endl;
    }
    return 0;
}
