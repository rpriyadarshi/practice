//
//  main.cpp
//  ReplaceSpace
//
//  Created by Rohit Priyadarshi on 12/1/12.
//  Copyright (c) 2012 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>

const char* replace_space(const char* str)
{
    const char* p1 = str;
    int spc_cnt = 0;
    size_t len = 0;
    while (*p1) {
        if(*p1 == ' ') {
            ++spc_cnt;
        }
        ++len;
        ++p1;
    }
    
    const char* repl = "%20";
    const size_t rlen = strlen(repl);
    size_t new_len = len + spc_cnt * (rlen - 1);
    char* n = new char[sizeof(char)*new_len];
    
    p1 = str;
    char* p2 = n;
    
    while (*p1) {
        if (*p1 == ' ') {
            strncpy(p2, repl, 3);
            p2 += rlen;
        } else {
            *p2 = *p1;
            ++p2;
        }
        ++p1;
    }
    
    return n;
}

int main(int argc, const char * argv[])
{
    const char* s1 = replace_space("Hello, this is out of this World!");
    std::cout << s1 << std::endl;
    delete s1;
    return 0;
}

