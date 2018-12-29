//
//  main.cpp
//  anagram_cluster
//
//  Created by Rohit Priyadarshi on 11/18/18.
//  Copyright © 2018 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

int main(int argc, const char * argv[]) {
    std::unordered_multimap<std::string, std::string> col;
    std::vector<std::string> data {"spot", "allergy", "stressed", "gallery", "stop", "largely", "desserts", "regally", "frame"};
    
    for (auto& s : data) {
        std::string key(s);
        std::sort(key.begin(), key.end());
        col.insert(std::pair<std::string, std::string>(key, s));
    }

    for (auto& c : col) {
        std::cout << c.second << " ";
    }
    std::cout << std::endl;
    return 0;
}
