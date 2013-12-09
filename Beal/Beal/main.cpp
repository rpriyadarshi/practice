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

unsigned short copy_builtin[] = {
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b1000000000000000,
    0b1000000000000000
    
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

void printConstants()
{
    std::cout << "long                  : " << sizeof(long) << std::endl;
    std::cout << "short                 : " << sizeof(short) << std::endl;
    std::cout << "int                   : " << sizeof(int) << std::endl;
    std::cout << "ULongToUShort         : " << Beal::ULongToUShort << std::endl;
    std::cout << "SizetToUShort         : " << Beal::SizetToUShort << std::endl;
    std::cout << "IntToUShort           : " << Beal::IntToUShort << std::endl;
    std::cout << "ByteBits              : " << Beal::ByteBits << std::endl;
    std::cout << "UShortBits            : " << Beal::UShortBits << std::endl;
    std::cout << "ULongBits             : " << Beal::ULongBits << std::endl;
    std::cout << "IntBits               : " << Beal::IntBits << std::endl;
    std::cout << "BigIntLongFact        : " << Beal::BigIntLongFact << std::endl;
    std::cout << "BigIntUShortFact      : " << Beal::BigIntUShortFact << std::endl;
    std::cout << "BigIntUShortMultFact  : " << Beal::BigIntUShortMultFact << std::endl;
    std::cout << "sizeof(BigInt)        : " << sizeof(Beal::BigInt) << std::endl;
}

void testBigIntCopyBigInt()
{
    Beal::BigInt u;
    for (size_t i = 0; i < Beal::BigIntUShortFact; ++i) {
        u[i] = i;
    }
    Beal::BigInt v(u);
    
    if (! v.validate(copy, sizeof(copy))) {
        std::cout << u << std::endl;
        std::cout << v << std::endl;
        std::cout << " @ copy failed!" << std::endl;
    }
}

void testBigIntCopySizet()
{
    size_t u = 2147516416;
    Beal::BigInt v(u);
    
    if (! v.validate(copy_builtin, sizeof(copy_builtin))) {
        std::cout << u << std::endl;
        std::cout << v << std::endl;
        std::cout << " @ copy failed!" << std::endl;
    }
}

void testBigIntCopyInt()
{
    int u = 2147516416;
    Beal::BigInt v(u);
    
    if (! v.validate(copy_builtin, sizeof(copy_builtin))) {
        std::cout << u << std::endl;
        std::cout << v << std::endl;
        std::cout << " @ copy failed!" << std::endl;
    }
}

void testBigIntFuncAdd()
{
    Beal::BigInt u, v, w;
    for (size_t i = 0; i < Beal::BigIntUShortFact / 2; ++i) {
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
    for (size_t i = 0; i < Beal::BigIntUShortFact / 2; ++i) {
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
    for (size_t i = 0; i < Beal::BigIntUShortFact / 2; ++i) {
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
    for (size_t i = 0; i < Beal::BigIntUShortFact / 2; ++i) {
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
    for (size_t i = 0; i < Beal::BigIntUShortFact / 2; ++i) {
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
    for (size_t i = 0; i < Beal::BigIntUShortFact / 2; ++i) {
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
    testBigIntCopyBigInt();
    testBigIntCopySizet();
    testBigIntCopyInt();
    
    testBigIntFuncAdd();
    testBigIntExtAdd();
    testBigIntIntAdd();
    
    testBigIntFuncMul();
    testBigIntExtMul();
    testBigIntIntMul();
    
    //testBeal<int>();
    testBeal<size_t>();
    //testBeal<Beal::BigInt>();
    printConstants();
    return 0;
}

