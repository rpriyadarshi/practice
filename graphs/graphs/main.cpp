//
//  main.cpp
//  graphs
//
//  Created by Rohit Priyadarshi on 2/22/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#include "adt.hpp"
#include "edgetote.hpp"
#include "edgebuilder.hpp"
#include "bellmanford.hpp"
#include "floydwarshall.hpp"

void runtest(const std::string& filename) {
    adt::factory fac;
    adt::graph<adt::vertexTote, adt::edgeTote> g;
    
    adt::builder<adt::vertexTote, adt::edgeTote> b(g);
    b.read(filename, fac);
//    std::cout << g << std::endl;
    
    adt::bellmanford<adt::vertexTote, adt::edgeTote> bf(g);
    bf();
    std::cout << "BF: " << bf << std::endl;
    
    adt::floydwarshall<adt::vertexTote, adt::edgeTote> fw(g);
    fw();
    std::cout << "FW: " << fw << std::endl;
    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
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

    runtest(input_random_1_2);
    runtest(input_random_4_2);
    runtest(input_random_8_4);
    runtest(input_random_10_8);
    runtest(input_random_13_16);
    runtest(input_random_15_16);
    runtest(input_random_20_32);
    runtest(input_random_30_256);
    runtest(input_random_44_2048);

    runtest(wikipedia);

//    runtest(g1);
//    runtest(g2);
//    runtest(g3);
//    runtest(large);

    return 0;
}
