//
//  main.cpp
//  RemoveDuplicateChar
//
//  Created by Rohit Priyadarshi on 11/30/12.
//  Copyright (c) 2012 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>

void remove_duplicate_chars(char* str)
{
    char * p1 = str;
    const char * p2 = str;
    const int MAX_FOLDS = 4;
    const int MAX_BITS = 32;
    
    int saved[MAX_FOLDS];
    memset(saved, 0, sizeof(saved));
    
    while (*p2 != '\0') {
        char c = *p2;
        int q = c / MAX_BITS;
        int r = c % MAX_BITS;
        int m = 1 << r;
        if (! (saved[q] & m)) {
            *p1++ = c;
            saved[q] |= m;
        }
        p2++;
    }
    *p1 = '\0';
}

int main(int argc, const char * argv[])
{
    char* s1 = strdup("aaaaaaaaa");
    char* s2 = strdup("abcdefgha");
    char* s3 = strdup("abcdefghi");
    char* s4 = strdup("abcdefghi abcdefghi abcdefghi abcdefghi");
    
    std::cout << s1 << " -> ";
    remove_duplicate_chars(s1);
    std::cout << s1 << std::endl;
    
    std::cout << s2 << " -> ";
    remove_duplicate_chars(s2);
    std::cout << s2 << std::endl;

    std::cout << s3 << " -> ";
    remove_duplicate_chars(s3);
    std::cout << s3 << std::endl;
    
    std::cout << s4 << " -> ";
    remove_duplicate_chars(s4);
    std::cout << s4 << std::endl;

    delete s1;
    delete s2;
    delete s3;
    delete s4;
    
    return 0;
}

