//
//  main.cpp
//  graphs
//
//  Created by Rohit Priyadarshi on 2/22/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#include "adt.hpp"
#include "tote.hpp"
#include "builder.hpp"
#include "bellmanford.hpp"
#include "floydwarshall.hpp"
#include "testers.hpp"

void runedgetest(const std::string& filename) {
    adt::testers<adt::vertexTote, adt::edgeTote> tst;
    tst.bldedge(filename);
    tst.runbelf();
    tst.runflw();
    std::cout << std::endl;
}

void runadjlisttest(const std::string& filename) {
    adt::testers<adt::vertexTote, adt::edgeTote> tst;
    tst.bldadjlist(filename);
    std::cout << std::endl;
}

void runedgetests() {
    // Load files
    const std::string path("/Users/rohit/Documents/Development/practice/graphs/graphs/adt/builders/edge/testcases/");
    // course
    const std::string g1(path + "g1.txt");                                      // NULL
    const std::string g2(path + "g2.txt");                                      // NULL
    const std::string g3(path + "g3.txt");                                      // -19
    const std::string large(path + "large.txt");
    
    const std::string wikipedia(path + "wikipedia.txt");                        //
    
    const std::string input_random_1_2(path + "input_random_1_2.txt");          // NULL
    const std::string input_random_4_2(path + "input_random_4_2.txt");          // -54
    const std::string input_random_8_4(path + "input_random_8_4.txt");          // -36
    const std::string input_random_10_8(path + "input_random_10_8.txt");        // -41
    const std::string input_random_13_16(path + "input_random_13_16.txt");      // NULL
    const std::string input_random_15_16(path + "input_random_15_16.txt");      // -100
    const std::string input_random_20_32(path + "input_random_20_32.txt");      // -242
    const std::string input_random_30_256(path + "input_random_30_256.txt");    // -961
    const std::string input_random_44_2048(path + "input_random_44_2048.txt");  // -3127

    runedgetest(input_random_1_2);
    runedgetest(input_random_4_2);
    runedgetest(input_random_8_4);
    runedgetest(input_random_10_8);
    runedgetest(input_random_13_16);
    runedgetest(input_random_15_16);
    runedgetest(input_random_20_32);
    runedgetest(input_random_30_256);
//    runedgetest(input_random_44_2048);

    runedgetest(wikipedia);

//    runedgetest(g1);
//    runedgetest(g2);
//    runedgetest(g3);
//    runedgetest(large);
}

void runadjlisttests() {
    // Load files
    const std::string path("/Users/rohit/Documents/Development/practice/graphs/graphs/adt/builders/adjacencylist/testcases/");
    // course
    const std::string dijkstraSmallData(path + "dijkstraSmallData.txt");        //
    const std::string dijkstraData(path + "dijkstraData.txt");                  //

    runadjlisttest(dijkstraSmallData);
    runadjlisttest(dijkstraData);
}

int main(int argc, const char * argv[]) {
    runedgetests();
    runadjlisttests();
    return 0;
}
