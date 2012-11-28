//
//  main.cpp
//  UniqueStringChar
//
//  Created by Rohit Priyadarshi on 4/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <string>

bool has_unique_chars(const std::string& s)
{
    const int MAX_FOLDS = 4;
    const int MAX_BITS = 32;
    int used[MAX_FOLDS];
    
    memset(used, 0, sizeof(used));
    for (int i = 0; i < s.size(); ++i) {
        int q = s[i] / MAX_BITS;
        int r = s[i] % MAX_BITS;
        int m = 1 << r;
        
        if (used[q] & m) {
            return false;
        }
        used[q] |= m;
    }

    return true;
}

void check_unique_chars(const std::string& s)
{
    if (has_unique_chars(s)) {
        std::cout << s << " has unique chars" << std::endl;
    } else {
        std::cout << s << " has repeated chars" << std::endl;
    }
}

int main (int argc, const char * argv[])
{
    std::string s1("abcdefghijklmnopqrst");
    std::string s2("abcdefghijklmnopqrsta");
    check_unique_chars(s1);
    check_unique_chars(s2);
    return 0;
}

