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
    
    class Vector
    {
    public:
        explicit Vector(size_t s);
        ~Vector();
        
        size_t& operator[](size_t i) const;
        size_t size() const { return _size; }
        void print(std::ostream& o) const;
        
    private:
        size_t& data(size_t idx) const { return _data[idx]; }
        void fill();
        void linear();
        
    private:
        size_t  _size;
        size_t* _data;
    };
    
    std::ostream& operator<<(std::ostream& o, Vector& v);

    class Array
    {
    public:
        Array(size_t x, size_t y);
        ~Array();
        
        size_t xSize() const { return _xSize; }
        size_t ySize() const { return _ySize; }
        
        size_t& operator[](size_t i) const;
        size_t& operator()(size_t x, size_t y) const;
        size_t& data(size_t x, size_t y) const;
        size_t index(size_t x, size_t y) const;
        void print(std::ostream& o) const;
        
    private:
        size_t& data(size_t idx) const { return _data[idx]; }
        void fill();
        void linear();
        void power(size_t y);
        
    private:
        size_t  _xSize;
        size_t  _ySize;
        size_t* _data;
    };
    
    std::ostream& operator<<(std::ostream& o, Array& a);
    
    class Cache
    {
    public:
        Cache(size_t x, size_t y);
        ~Cache();
        
        const Array& table() const { return _table; }
        const Vector& helper() const { return _helper; }
        
        const size_t& power(size_t i) const;
        const size_t& power(size_t x, size_t y) const;
        const size_t& table(size_t i) const { return table()[i]; }
        const size_t& helper(size_t i) const { return helper()[i]; }
        
        bool checkSort() const;
        void sort();
        size_t find(size_t v) const;
        bool calculate(size_t a, size_t x, size_t b, size_t y) const;
        void print(std::ostream& o) const;

    private:
        Array& table() { return _table; }
        Vector& helper() { return _helper; }
        
        size_t& power(size_t i);
        size_t& power(size_t x, size_t y);
        size_t& table(size_t i) { return table()[i]; }
        size_t& helper(size_t i) { return helper()[i]; }
        
        bool checkSort(size_t i, size_t j) const;
        void merge(size_t x1, size_t x2, size_t y1, size_t y2);
        
    private:
        Array   _table;
        Vector  _helper;
    };
    
    std::ostream& operator<<(std::ostream& o, Cache& c);
}

#endif
