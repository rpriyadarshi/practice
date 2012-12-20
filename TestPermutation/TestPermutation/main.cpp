//
//  main.cpp
//  TestPermutation
//
//  Created by Rohit Priyadarshi on 12/19/12.
//  Copyright (c) 2012 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>

bool arePermutations(const char* s1, const char* s2)
{
    const int MAX_CHARS = 128;
    int a1[MAX_CHARS];
    int a2[MAX_CHARS];
    memset(a1, 0, sizeof(a1));
    memset(a2, 0, sizeof(a2));
    
    const char* p1 = s1;
    const char* p2 = s2;
    
    while (*p1 && *p2) {
        ++a1[*p1++];
        ++a2[*p2++];
    }
    if (*p1 || *p2) {
        return false;
    }
    for (int i = 0; i < MAX_CHARS; ++i) {
        if (a1[i] != a2[i]) {
            return false;
        }
    }
    
    return true;
}

void testPermutation(const char* s1, const char* s2)
{
    if (arePermutations(s1, s2)) {
        std::cout << s1 << " is a permutation of " << s2 << std::endl;
    } else {
        std::cout << s1 << " is a NOT permutation of " << s2 << std::endl;
    }
}

int main(int argc, const char * argv[])
{
    testPermutation("abcdef", "fbdace");
    testPermutation("abcdef", "fbdac");
    testPermutation("abcdefabcdef", "abcdef");
    return 0;
}

