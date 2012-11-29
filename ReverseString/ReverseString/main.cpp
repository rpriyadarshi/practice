//
//  main.cpp
//  ReverseString
//
//  Created by Rohit Priyadarshi on 11/28/12.
//  Copyright (c) 2012 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>

void reverse(char* str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len/2; ++i) {
        char c = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = c;
    }
}

int main(int argc, const char * argv[])
{
    char str[] = "Hello, World";
    std::cout << str << std::endl;
    reverse(str);
    std::cout << str << std::endl;
    
    return 0;
}

