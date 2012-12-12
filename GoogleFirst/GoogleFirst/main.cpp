//
//  main.cpp
//  GoogleFirst
//
//  Created by Rohit Priyadarshi on 12/11/12.
//  Copyright (c) 2012 Rohit Priyadarshi. All rights reserved.
//
//  Hi Rohit!
//  
//  Hello
//  
//  Write a function that, given an array of integers that represents a
//  decimal number, increments that decimal number by one.
//  
//  Example:
//  
//  123 + 1 = 124
//  [1, 2, 3] → [1, 2, 4]
//  
//  789 + 1 = 790
//  [7, 8, 9] → [7, 9, 0]
//  
//  3896 + 1 = 3897
//  [3, 8, 9, 6] → [3, 8, 9, 7]
//  

#include <iostream>
bool increment(int* a, int size)
{
    int i = size - 1;
    int sum = a[i] + 1;
    bool carry = sum == 10 ? true : false;
    sum = carry == false ? sum : 0;
    a[i] = sum;
    --i;
    for (; carry && i >= 0; --i) {
        sum = a[i] + 1;
        carry = sum == 10 ? true : false;
        sum = carry == false ? sum : 0;
        a[i] = sum;
    }
    
    return carry;
}

void print(int* a, int size)
{
    for (int i = 0; i < size; ++i) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

void test(int* a, int size)
{
    print(a, size);
    bool carry = increment(a, size);
    if (carry) {
        std::cout << "Overflow occured" << std::endl;
    }
    print(a, size);    
}

int main(int argc, const char * argv[])
{
    int a[] = {1, 2, 3};
    test(a, sizeof(a)/sizeof(int));
    int b[] = {7, 8, 9};
    test(b, sizeof(b)/sizeof(int));
    int c[] = {3, 8, 9, 6};
    test(c, sizeof(c)/sizeof(int));
    int d[] = {9, 9, 9, 9};
    test(d, sizeof(d)/sizeof(int));

    return 0;
}

