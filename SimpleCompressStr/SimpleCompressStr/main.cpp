//
//  main.cpp
//  SimpleCompressStr
//
//  Created by Rohit Priyadarshi on 12/22/12.
//  Copyright (c) 2012 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>

bool compress(const char* str, char* r_str)
{
    int cnt = 1;
    size_t l;
    char* r = r_str;

    const char* p = str;
    const char* prev_p = str;
    
    *r++ = *p++;
    
    while (*prev_p) {
        if (*prev_p == *p) {
            cnt++;
        } else {
            sprintf(r, "%d", cnt);
            l = strlen(r);
            r += l;
            *r++ = *p;
            cnt = 1;
        }
        prev_p++;
        p++;
    }
    
    if (p - str > r - r_str) {
        return true;
    }
    
    return false;
}

void check_compress(const char* str)
{
    if (! str) return;
    char* r_str = new char(strlen(str)*2);
    bool status = compress(str, r_str);
    if (status) {
        std::cout << "Compressed " << str << " to " << r_str << std::endl;
    } else {
        std::cout << "Cannot compress " << str << std::endl;
    }
    delete r_str;
}

int main(int argc, const char * argv[])
{
    check_compress("");
    check_compress("a");
    check_compress("aa");
    check_compress("aaa");
    check_compress("abcdefg");
    check_compress("aaabcccdddeeeefgg");
    return 0;
}

