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

int main(int argc, const char * argv[]) {
    adt::factory fac;
    adt::graph<adt::vertexTote, adt::edgeTote> g;
    
    // Load files
    const std::string path("/Users/rohit/Documents/Development/practice/graphs/graphs/adt/builders/edge/testcases/");
    // course
    const std::string g1(path + "g1.txt");
    const std::string g2(path + "g2.txt");
    const std::string g3(path + "g3.txt");
    const std::string large(path + "glarge.txt");
    
    // fail
    const std::string input_random_1_2(path + "input_random_1_2.txt");
    // pass
    const std::string input_random_4_2(path + "input_random_4_2.txt");
    const std::string input_random_8_4(path + "input_random_8_4.txt");
    const std::string input_random_10_8(path + "input_random_10_8.txt");
    // fail
    const std::string input_random_13_16(path + "input_random_13_16.txt");
    // pass
    const std::string input_random_15_16(path + "input_random_15_16.txt");
    const std::string input_random_20_32(path + "input_random_20_32.txt");

    adt::builder<adt::vertexTote, adt::edgeTote> b(g);
    b.read(input_random_1_2, fac);
    std::cout << g << std::endl;
    
    adt::bellmanford<adt::vertexTote, adt::edgeTote> bf(g);
    std::cout << bf() << std::endl;
    
    return 0;
}
