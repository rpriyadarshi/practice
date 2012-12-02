//
//  main.cpp
//  Anagrams
//
//  Created by Rohit Priyadarshi on 12/1/12.
//  Copyright (c) 2012 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>

bool are_anagrams(const char* s1, const char* s2)
{
    const int MAX_CHARS = 128;
    int u1[MAX_CHARS], u2[MAX_CHARS];
    memset(u1, 0, sizeof(u1));
    memset(u2, 0, sizeof(u2));
    
    const char* p1 = s1;
    const char* p2 = s2;
    int l1 = 0, l2 = 0;
    
    while (*p1) {
        ++u1[*p1];
        ++l1;
        ++p1;
    }
    while (*p2) {
        ++u2[*p2];
        ++l2;
        ++p2;
    }
    
    if (l1 != l2) {
        return false;
    }
    for (int i = 0; i < l1; ++i)
    {
        if (u1[i] != u2[i]) {
            return false;
        }
    }
    return true;
}

void check_anagram(const char* s1, const char* s2)
{
    std::cout << s1 << " and " << s2;
    if (are_anagrams(s1, s2)) {
        std::cout << " are anagrams" << std::endl;
    } else {
        std::cout << " are not anagrams" << std::endl;
    }
}

int main(int argc, const char * argv[])
{
    char* s1 = strdup("abcdefghijklmnopqrstuvwxyz");
    char* s2 = strdup("aklvwmnobcdpqrstuefghijxyz");
    char* s3 = strdup("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
    char* s4 = strdup("abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba");
    check_anagram(s1, s2);
    check_anagram(s2, s3);
    check_anagram(s3, s4);
    return 0;
}

