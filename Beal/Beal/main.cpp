//
//  main.cpp
//  Beal
//
//  Created by Rohit Priyadarshi on 6/8/13.
//  Copyright (c) 2013 Rohit Priyadarshi. All rights reserved.
//

#include "beal_impl.h"

unsigned short copy[] = {
    0b0000000000001111,
    0b0000000000001110,
    0b0000000000001101,
    0b0000000000001100,
    0b0000000000001011,
    0b0000000000001010,
    0b0000000000001001,
    0b0000000000001000,
    0b0000000000000111,
    0b0000000000000110,
    0b0000000000000101,
    0b0000000000000100,
    0b0000000000000011,
    0b0000000000000010,
    0b0000000000000001,
    0b0000000000000000
    
};

unsigned short add[] = {
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000010,
    0b0000000000000010,
    0b0000000000000010,
    0b0000000000000010,
    0b0000000000000010,
    0b0000000000000010,
    0b0000000000000010,
    0b0000000000000010
};

unsigned short mul[] = {
    0b0000000000000000,
    0b0000000000000001,
    0b0000000000000010,
    0b0000000000000011,
    0b0000000000000100,
    0b0000000000000101,
    0b0000000000000110,
    0b0000000000000111,
    0b0000000000001000,
    0b0000000000000111,
    0b0000000000000110,
    0b0000000000000101,
    0b0000000000000100,
    0b0000000000000011,
    0b0000000000000010,
    0b0000000000000001
};

void testBigIntCopy()
{
    Beal::BigInt u;
    for (size_t i = 0; i < Beal::Size; ++i) {
        u[i] = i;
    }
    Beal::BigInt v(u);
    
    if (! v.validate(copy, sizeof(copy))) {
        std::cout << u << std::endl;
        std::cout << v << std::endl;
        std::cout << " @ copy failed!" << std::endl;
    }
}

void testBigIntFuncAdd()
{
    Beal::BigInt u, v, w;
    for (size_t i = 0; i < Beal::Size / 2; ++i) {
        u[i] = 1;
        v[i] = 1;
    }
    
    w.add(u, v);
    
    if (! w.validate(add, sizeof(add))) {
        std::cout << u << std::endl;
        std::cout << v << std::endl;
        std::cout << w << std::endl;
        std::cout << " @ + failed!" << std::endl;
    }
}

void testBigIntIntAdd()
{
    Beal::BigInt u, v, w, x;
    for (size_t i = 0; i < Beal::Size / 2; ++i) {
        u[i] = 1;
        v[i] = 1;
    }
    
    v += u;
    
    if (! v.validate(add, sizeof(add))) {
        std::cout << u << std::endl;
        std::cout << v << std::endl;
        std::cout << " @ += failed!" << std::endl;
    }
}

void testBigIntExtAdd()
{
    Beal::BigInt u, v, w;
    for (size_t i = 0; i < Beal::Size / 2; ++i) {
        u[i] = 1;
        v[i] = 1;
    }
    
    w = u + v;
    
    if (! w.validate(add, sizeof(add))) {
        std::cout << u << std::endl;
        std::cout << v << std::endl;
        std::cout << w << std::endl;
        std::cout << " @ + failed!" << std::endl;
    }
}

void testBigIntFuncMul()
{
    Beal::BigInt u, v, w;
    for (size_t i = 0; i < Beal::Size / 2; ++i) {
        u[i] = 1;
        v[i] = 1;
    }
    
    w.muliply(v, u);
    
    if (! w.validate(mul, sizeof(mul))) {
        std::cout << u << std::endl;
        std::cout << v << std::endl;
        std::cout << " @ *= failed!" << std::endl;
    }
}

void testBigIntIntMul()
{
    Beal::BigInt u, v;
    for (size_t i = 0; i < Beal::Size / 2; ++i) {
        u[i] = 1;
        v[i] = 1;
    }
    
    v *= u;
    
    if (! v.validate(mul, sizeof(mul))) {
        std::cout << u << std::endl;
        std::cout << v << std::endl;
        std::cout << " @ *= failed!" << std::endl;
    }
}

void testBigIntExtMul()
{
    Beal::BigInt u, v, w;
    for (size_t i = 0; i < Beal::Size / 2; ++i) {
        u[i] = 1;
        v[i] = 1;
    }
    
    w = u * v;
    
    if (! w.validate(mul, sizeof(mul))) {
        std::cout << u << std::endl;
        std::cout << v << std::endl;
        std::cout << w << std::endl;
        std::cout << " @ * failed!" << std::endl;
    }
}

template <typename T>
void testBeal()
{
    Beal::Cache<T> beal(25, 10);
    beal.sort();
    
    // 3^3 + 6^3 = 3^5
    size_t a = 3, x = 3, b = 6, y = 3, c, z;
    beal.calculate(a, x, b, y, c, z);
    beal.print(std::cout, a, x, b, y, c, z);
    
    // 7^6 + 7^7 = 98^3
    a = 7; x = 6; b = 7; y = 7;
    beal.calculate(a, x, b, y, c, z);
    beal.print(std::cout, a, x, b, y, c, z);
    
    beal.search();    
}

int main(int argc, const char * argv[])
{
    testBigIntCopy();
    
    testBigIntFuncAdd();
    testBigIntExtAdd();
    testBigIntIntAdd();
    
    testBigIntFuncMul();
    testBigIntExtMul();
    testBigIntIntMul();
    
    //testBeal<size_t>();
    //testBeal<int>();
    //testBeal<Beal::BigInt>();
    return 0;
}

