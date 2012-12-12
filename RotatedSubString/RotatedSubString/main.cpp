//
//  main.cpp
//  RotatedSubString
//
//  Created by Rohit Priyadarshi on 12/11/12.
//  Copyright (c) 2012 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>

bool is_rotation(const std::string& s1, const std::string& s2)
{
    std::string s = s2 + s2;
    return s.find(s1);
}

int main(int argc, const char * argv[])
{
    std::string s1("waterbottle");
    std::string s2("erbottlewat");
    bool status = is_rotation(s1, s2);
    if (! status) {
        std::cout << s1 << " not a rotation of " << s2 << std::endl;
    } else {
        std::cout << s1 << " a rotation of " << s2 << std::endl;
    }
    return 0;
}

