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
    
    constexpr const unsigned long ULongToUShort     = sizeof(unsigned long) / sizeof(unsigned short);
    constexpr const unsigned long SizetToUShort     = sizeof(size_t) / sizeof(unsigned short);
    constexpr const unsigned long IntToUShort       = sizeof(int) / sizeof(unsigned short);

    constexpr const unsigned long ByteSize          = 8;
    constexpr const unsigned long UShortSize        = sizeof(unsigned short) * ByteSize;
    constexpr const unsigned long ULongSize         = sizeof(unsigned long) * ByteSize;
    constexpr const unsigned long IntSize           = sizeof(int) * ByteSize;
    
    constexpr const unsigned long BigIntFact        = 4;
    constexpr const unsigned long BigIntSize        = ULongToUShort * BigIntFact;
    constexpr const unsigned long BigIntDataSize    = ULongToUShort * (BigIntFact << 2);

    class BigInt
    {
    public:
        BigInt() { zero(); }
        BigInt(const BigInt& v) { copy(v); }
        BigInt(const int& v) { copy(v); }
        BigInt(const size_t& v) { copy(v); }
        ~BigInt() {};
        
        size_t size() const { return BigIntSize; }
        size_t dataSize() const { return BigIntDataSize; }
        unsigned short& data(size_t idx) { return _data[idx]; }
        const unsigned short& data(size_t idx) const { return _data[idx]; }

        BigInt& add(const BigInt& u, const BigInt& v);
        BigInt& muliply(const BigInt& u, const BigInt& v);
        void zero() { memset(_data, 0, sizeof(_data)); }
        BigInt& copy(const BigInt& v) {
            if (&v != this) {
                memcpy(_data, v._data, dataSize());
            }
            return *this; }
        BigInt& copy(const size_t& v) {
            unsigned short x = 0;
            size_t y = v;
            size_t i = 0;
            for (; i < SizetToUShort; ++i) {
                x = y;
                y >>= UShortSize;
                data(i) = x;
            }
            for (; i < BigIntDataSize; ++i) {
                data(i) = 0;
            }
            return *this; }
        BigInt& copy(const int& v) {
            unsigned short x = 0;
            int y = v;
            size_t i = 0;
            for (; i < IntToUShort; ++i) {
                x = y;
                y >>= UShortSize;
                data(i) = x;
            }
            for (; i < BigIntDataSize; ++i) {
                data(i) = 0;
            }
            return *this; }
        
        bool validate(const unsigned short* mul, const size_t sz) const;
        
        void print(std::ostream& o) const;
        void printBits(std::ostream& o) const;
        
        // Operators
        unsigned short& operator[](size_t idx) { return data(idx); }
        BigInt& operator=(const BigInt& v) { return copy(v); }
        BigInt& operator=(const size_t& v) { return copy(v); }
        BigInt& operator=(const int& v) { return copy(v); }
        BigInt& operator*=(const BigInt& v) { BigInt u(*this); zero(); return muliply(u, v); }
        BigInt& operator+=(const BigInt& v) { BigInt u(*this); return add(u, v); }
        
    private:
        unsigned short  _data[BigIntDataSize];
    };
    
    BigInt operator+(const BigInt& u, const BigInt& v) { return BigInt(u) += v; }
    BigInt operator*(const BigInt& u, const BigInt& v) { return BigInt(u) *= v; }
    std::ostream& operator<<(std::ostream& o, const BigInt& b) { b.print(o); return o; }

    template <typename T>
    class Vector
    {
    public:
        explicit Vector(size_t s) : _size(s), _data(new T[s]) { fill(); }
        ~Vector() { delete _data; }
        
        T& operator[](size_t i) const { return data(i); }
        size_t size() const { return _size; }
        void print(std::ostream& o) const;
        
    private:
        T& data(size_t idx) const { return _data[idx]; }
        void fill() { linear(); }
        void linear() {
            for (size_t i = 0; i < size(); ++i) {
                data(i) = i;
            }
        }
        
    private:
        size_t  _size;
        T*      _data;
    };
    
    template <typename T>
    std::ostream& operator<<(std::ostream& o, const Vector<T>& v) { v.print(o); return o; }

    template <typename T>
    class Array
    {
    public:
        Array(size_t x, size_t y) : _xSize(x), _ySize(y), _data(new T[x * y]) { fill(); }
        ~Array() { delete _data; }
        
        size_t xSize() const { return _xSize; }
        size_t ySize() const { return _ySize; }
        
        T& operator[](size_t i) const { return data(i); }
        T& operator()(size_t x, size_t y) const { return data(x, y); }
        T& data(size_t x, size_t y) const { return data(index(x, y)); }
        size_t index(size_t x, size_t y) const { return x + y * xSize(); }
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
    std::ostream& operator<<(std::ostream& o, const Array<T>& a) { a.print(o); return o; }
    
    template <typename T>
    class Cache
    {
    public:
        Cache(size_t x, size_t y) : _table(x, y), _helper(x * y) {}
        ~Cache() {}
        
        const Array<T>& table() const { return _table; }
        const Vector<size_t>& helper() const { return _helper; }
        const bool error() const { return _error; }
        
        const T& power(size_t i) const { return table()[helper()[i]]; }
        const T& power(size_t x, const T& y) const { return power(table().index(x, y)); }
        const T& table(size_t i) const { return table()[i]; }
        const size_t& helper(size_t i) const { return helper()[i]; }
        
        bool checkSort() const;
        bool sort();
        size_t find(const T& v) const;
        bool search() const;
        bool calculate(size_t a, size_t x, size_t b, size_t y, size_t& c, size_t& z) const;
        size_t coefficient(size_t idx) const { return idx % table().xSize(); }
        size_t exponent(size_t idx) const { return idx / table().xSize(); }
        
        void print(std::ostream& o) const;
        void print(std::ostream& o, size_t a, size_t x, size_t b, size_t y, size_t c, size_t z) const;

    private:
        Array<T>& table() { return _table; }
        Vector<size_t>& helper() { return _helper; }
        void error(bool e) const { _error = e; }

        T& power(size_t i) { return table()[helper()[i]]; }
        T& power(size_t x, size_t y) { return power(table().index(x, y)); }
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
    std::ostream& operator<<(std::ostream& o, const Cache<T>& c) { c.print(o); return o; }
}

#endif
