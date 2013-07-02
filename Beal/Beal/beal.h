//
//  beal.h
//  Beal
//
//  Created by Rohit Priyadarshi on 6/11/13.
//  Copyright (c) 2013 Rohit Priyadarshi. All rights reserved.
//

#ifndef Beal_beal_h
#define Beal_beal_h

#include <iostream>
#include <assert.h>
#include <math.h>

namespace Beal {
    template <typename T> T Min(T& t1, T& t2) { return t1 < t2 ? t1 : t2; }
    template <typename T> T Max(T& t1, T& t2) { return t1 > t2 ? t1 : t2; }
    
    const unsigned long Word = 8;
    const unsigned long LongToShort = sizeof(unsigned long) / sizeof(unsigned short);
    const unsigned long ShortSize = sizeof(unsigned short) * Word;
    const unsigned long BigIntSize = 2;
    const unsigned long Size = LongToShort * BigIntSize;

    class BigInt
    {
    public:
        BigInt();
        ~BigInt() {};
        
        size_t size() const;
        unsigned short& data(size_t idx);
        const unsigned short& data(size_t idx) const;

        BigInt& add(const BigInt& u, const BigInt& v);
        BigInt& muliply(const BigInt& u, const BigInt& v);
        
        void print(std::ostream& o) const;
        
        // Operators
        unsigned short& operator[](size_t idx);
        
    private:
        typedef union {
            unsigned long    _uint;
            unsigned short  _sint[LongToShort];
        } IntType;
        IntType _data[BigIntSize];
    };
    
    BigInt& operator+(const BigInt& u, const BigInt& v);
    BigInt& operator*(const BigInt& u, const BigInt& v);
    std::ostream& operator<<(std::ostream& o, const BigInt& b);

    template <typename T>
    class Vector
    {
    public:
        explicit Vector(size_t s);
        ~Vector();
        
        T& operator[](size_t i) const;
        size_t size() const { return _size; }
        void print(std::ostream& o) const;
        
    private:
        T& data(size_t idx) const { return _data[idx]; }
        void fill();
        void linear();
        
    private:
        size_t  _size;
        T*      _data;
    };
    
    template <typename T>
    std::ostream& operator<<(std::ostream& o, const Vector<T>& v);

    template <typename T>
    class Array
    {
    public:
        Array(size_t x, size_t y);
        ~Array();
        
        size_t xSize() const { return _xSize; }
        size_t ySize() const { return _ySize; }
        
        T& operator[](size_t i) const;
        T& operator()(size_t x, size_t y) const;
        T& data(size_t x, size_t y) const;
        size_t index(size_t x, size_t y) const;
        void print(std::ostream& o) const;
        
    private:
        T& data(size_t idx) const { return _data[idx]; }
        void fill();
        void linear();
        void power(size_t y);
        
    private:
        size_t  _xSize;
        size_t  _ySize;
        T*      _data;
    };
    
    template <typename T>
    std::ostream& operator<<(std::ostream& o, const Array<T>& a);
    
    template <typename T>
    class Cache
    {
    public:
        Cache(size_t x, size_t y);
        ~Cache();
        
        const Array<T>& table() const { return _table; }
        const Vector<size_t>& helper() const { return _helper; }
        const bool error() const { return _error; }
        
        const T& power(size_t i) const;
        const T& power(size_t x, size_t y) const;
        const T& table(size_t i) const { return table()[i]; }
        const size_t& helper(size_t i) const { return helper()[i]; }
        
        bool checkSort() const;
        bool sort();
        size_t find(T v) const;
        bool search() const;
        bool calculate(size_t a, size_t x, size_t b, size_t y, size_t& c, size_t& z) const;
        size_t coefficient(size_t idx) const;
        size_t exponent(size_t idx) const;
        
        void print(std::ostream& o) const;
        void print(std::ostream& o, size_t a, size_t x, size_t b, size_t y, size_t c, size_t z) const;

    private:
        Array<T>& table() { return _table; }
        Vector<size_t>& helper() { return _helper; }
        void error(bool e) const { _error = e; }

        T& power(size_t i);
        T& power(size_t x, size_t y);
        T& table(size_t i) { return table()[i]; }
        size_t& helper(size_t i) { return helper()[i]; }
        
        bool checkSort(size_t i, size_t j) const;
        void merge(size_t x1, size_t x2, size_t y1, size_t y2);
        bool search(size_t a, size_t x, size_t b, size_t y, size_t& c, size_t& z) const;
        
    private:
        Array<T>        _table;
        Vector<size_t>  _helper;
        mutable bool    _error;
    };
    
    template <typename T>
    std::ostream& operator<<(std::ostream& o, const Cache<T>& c);
}

#endif
