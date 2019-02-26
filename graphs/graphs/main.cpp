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

int main(int argc, const char * argv[]) {
    adt::factory fac;
    adt::graph<eb::vertexTote, eb::edgeTote> g;
    
    // Load files
    const std::string path("/Users/rohit/Documents/Development/practice/graphs/graphs/eb/builders/edge/testcases/");
    const std::string g1(path + "g1.txt");
    const std::string g2(path + "g2.txt");
    const std::string g3(path + "g3.txt");
    const std::string large(path + "glarge.txt");
    
    eb::builder<eb::vertexTote, eb::edgeTote> b(g);
    b.read(g1, fac);
    std::cout << g << std::endl;
    
    return 0;
}
