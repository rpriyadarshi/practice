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

namespace Beal {
    template <typename T> T Min(T& t1, T& t2) { return t1 < t2 ? t1 : t2; }
    template <typename T> T Max(T& t1, T& t2) { return t1 > t2 ? t1 : t2; }
    
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
    std::ostream& operator<<(std::ostream& o, Vector<T>& v);

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
    std::ostream& operator<<(std::ostream& o, Array<T>& a);
    
    template <typename T>
    class Cache
    {
    public:
        Cache(size_t x, size_t y);
        ~Cache();
        
        const Array<T>& table() const { return _table; }
        const Vector<T>& helper() const { return _helper; }
        
        const T& power(size_t i) const;
        const T& power(size_t x, size_t y) const;
        const T& table(size_t i) const { return table()[i]; }
        const T& helper(size_t i) const { return helper()[i]; }
        
        bool checkSort() const;
        void sort();
        size_t find(T v) const;
        bool search() const;
        bool calculate(T a, T x, T b, T y, T& c, T& z) const;
        
        void print(std::ostream& o) const;
        void print(std::ostream& o, T a, T x, T b, T y, T c, T z) const;

    private:
        Array<T>& table() { return _table; }
        Vector<T>& helper() { return _helper; }
        
        T& power(size_t i);
        T& power(size_t x, size_t y);
        T& table(size_t i) { return table()[i]; }
        T& helper(size_t i) { return helper()[i]; }
        
        bool checkSort(size_t i, size_t j) const;
        void merge(size_t x1, size_t x2, size_t y1, size_t y2);
        bool search(T a, T x, T b, T y, T& c, T& z) const;
        
    private:
        Array<T>   _table;
        Vector<T>  _helper;
    };
    
    template <typename T>
    std::ostream& operator<<(std::ostream& o, Cache<T>& c);
}

#endif
