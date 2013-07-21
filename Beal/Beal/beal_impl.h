//
//  beal.cpp
//  Beal
//
//  Created by Rohit Priyadarshi on 6/11/13.
//  Copyright (c) 2013 Rohit Priyadarshi. All rights reserved.
//

#include "beal.h"

#ifndef Beal_beal_impl_h
#define Beal_beal_impl_h

//#define _DEBUG

namespace Beal {    
    BigInt& BigInt::add(const BigInt& u, const BigInt& v)
    {
        BigInt& w = *this;
        size_t s = size();
        
        for (size_t i = 0; i < s; ++i) {
            w.data(i) = u.data(i) + v.data(i);
        }
        return *this;
    }
    
    BigInt& BigInt::muliply(const BigInt& u, const BigInt& v)
    {
        BigInt& w = *this;
        const size_t s = size();
        
        for (size_t j = 0; j < s; ++j) {
            unsigned long _k = 0;
            for (size_t i = 0; i < s; ++i) {
                unsigned long _u = u.data(i);
                unsigned long _v = v.data(j);
                unsigned long _w = w.data(i + j);
                unsigned long _t = _u * _v + _w + _k;
                w.data(i + j) = _t;
                _k = _t >> UShortSize;
            }
            w.data(j + s) = _k;
        }
        return *this;
    }
    
    bool BigInt::validate(const unsigned short* val, const size_t sz) const
    {
        for (size_t i = 0; i < Beal::BigIntSize; ++i) {
            unsigned short d = data(Beal::BigIntSize - i - 1);
            unsigned short v = val[i];
            if (d != v) {
                return false;
            }
        }
        return true;
    }
    
    void BigInt::print(std::ostream& o) const
    {
        for (int i = 0; i < size(); ++i) {
            o << data(size() - i - 1) << " ";
        }
        std::cout << std::endl;
        printBits(o);
    }
    
    void BigInt::printBits(std::ostream& o) const
    {
        for (int i = 0; i < size(); ++i) {
            unsigned short d = data(size() - i - 1);
            std::cout << "[" << d << "] ";
            for (int j = 0; j < UShortSize; j++) {
                bool b = d & 0b1000000000000000;
                d <<= 1;
                o << b;
            }
            o << " ";
        }
        o << std::endl;
    }
            
    template <typename T>
    void Vector<T>::print(std::ostream& o) const
    {
        for (T i = 0; i < size(); ++i) {
            o << data(i) << " ";
        }
        o << std::endl;
    }
                    
    template <typename T>
    void Array<T>::fill()
    {
        linear();
        for (size_t y = 1; y < ySize(); ++y) {
            power(y);
        }
    }
    
    template <typename T>
    void Array<T>::linear()
    {
        size_t i = 1;
        for (size_t x = 0; x < xSize(); ++x) {
            data(x, 0) = static_cast<T>(i++);
        }
    }
    
    template <typename T>
    void Array<T>::power(size_t y)
    {
        for (size_t x = 0; x < xSize(); ++x) {
            data(x, y) = data(x, y - 1) * data(x, 0);
        }
    }
    
    template <typename T>
    void Array<T>::print(std::ostream& o) const
    {
        for (size_t y = 0; y < ySize(); ++y) {
            for (size_t x = 0; x < xSize(); ++x) {
                o << data(x, y) << " ";
            }
            o << std::endl;
        }
    }
                
    template <typename T>
    bool Cache<T>::checkSort(size_t i, size_t j) const
    {
        error(false);
        T p = power(i);
        for (size_t l = i + 1; l < j; ++l) {
            const T& c = power(l);
            if (c < p) {
                std::cout << "ERROR @ " << l << " " << p << " " << c << std::endl;
                std::cout << "        Likely cause is that you have overflow." << std::endl;
                error(true);
                return false;
            }
            p = c;
        }
        error(false);
        return true;
    }
    
    template <typename T>
    bool Cache<T>::checkSort() const
    {
        size_t l_max = table().xSize() * table().ySize();
        return checkSort(0, l_max);
    }
    
    template <typename T>
    bool Cache<T>::sort()
    {
        size_t l_max = table().xSize() * table().ySize();
        size_t l_step = table().xSize();
        while (l_step <= l_max) {
#ifdef _DEBUG
            std::cout << "SIZE - " << l_step << std::endl;
#endif
            size_t i = 0, j = 0, k = 0, l = 0;
            while (l < l_max) {
                i = l;
                l += l_step;
                j = l;
                l += l_step;
                k = l;
                if (j >= l_max) {
                    j -= l_step;
                    i -= l_step << 1;
                    k = l_max;
                } else if (k > l_max) {
                    k = l_max;
                }
                merge(i, j, j, k);
            }
            l_step <<= 1;
        }
#ifdef _DEBUG
        std::cout << std::endl;
#endif
        return checkSort();
    }

    template <typename T>
    void Cache<T>::merge(size_t i1, size_t i2, size_t j1, size_t j2)
    {
#ifdef _DEBUG
        std::cout << "BINS - " << i1 << " " << i2 << " " << j1 << " " << j2 << std::endl;
        checkSort(i1, i2);
        checkSort(j1, j2);
#endif
        size_t idx_size = i2 - i1 + j2 - j1;
        Vector<size_t> idx(idx_size);
        size_t i = i1;
        size_t j = j1;
        size_t k = 0;
        while (i < i2 && j < j2) {
            size_t idx_i = helper(i);
            size_t idx_j = helper(j);
            T v1 = table(idx_i);
            T v2 = table(idx_j);
            if (v1 < v2) {
                idx[k++] = idx_i;
                i++;
            } else if (v1 > v2) {
                idx[k++] = idx_j;
                j++;
            } else {
                idx[k++] = idx_i;
                idx[k++] = idx_j;
                i++;
                j++;
            }
        }
        while (i < i2) {
            idx[k++] = helper(i++);
        }
        while (j < j2) {
            idx[k++] = helper(j++);
        }
        assert(i == i2 || j == j2);
        assert(idx_size == k);
        k = 0;
        for (i = i1; i < i2; ++i) {
            helper(i) = idx[k++];
        }
        for (j = j1; j < j2; ++j) {
            helper(j) = idx[k++];
        }
    }
    
    template <typename T>
    size_t Cache<T>::find(T v) const
    {
        size_t l_min = 0;
        size_t l_max = helper().size();
        while (l_max - l_min > 1) {
            size_t w = (l_max - l_min) >> 1;
            size_t i = l_min + w;
            T p = power(i);
            if (v < p) {
                l_max = i;
            } else if (v > p) {
                l_min = i;
            } else {
                return helper()[i];
            }
        }
        return SIZE_T_MAX;
    }
        
    template <typename T>
    bool Cache<T>::calculate(size_t a, size_t x, size_t b, size_t y, size_t& c, size_t& z) const
    {
        if (error()) {
            return false;
        }
        bool status = search(a - 1, x - 1, b - 1, y - 1, c, z);
        c++;
        z++;
        return status;
    }
    
    template <typename T>
    bool Cache<T>::search() const
    {
        if (error()) {
            return false;
        }
        bool found = false;
        size_t l_max = table().xSize() * table().ySize();
        for (size_t i = 0; i < l_max; ++i) {
            T v1 = power(i);
            for (size_t j = 0; j < l_max; ++j) {
                T v2 = power(j);
                T v3 = v1 + v2;
                size_t idx3 = find(v3);
                if (idx3 == SIZE_T_MAX) {
                    continue;
                }
                found = true;
                
                size_t idx1 = helper(i);
                size_t idx2 = helper(j);
                
                size_t a = coefficient(idx1);
                size_t x = exponent(idx1);
                size_t b = coefficient(idx2);
                size_t y = exponent(idx2);
                size_t c = coefficient(idx3);
                size_t z = exponent(idx3);
                print(std::cout, a + 1, x + 1, b + 1, y + 1, c + 1, z + 1);
            }
        }
        return found;
    }
    
    template <typename T>
    bool Cache<T>::search(size_t a, size_t x, size_t b, size_t y, size_t& c, size_t& z) const
    {
        T v1 = table().data(a, x);
        T v2 = table().data(b, y);
        T v3 = v1 + v2;
        size_t idx3 = find(v3);
        if (idx3 == SIZE_T_MAX) {
            return false;
        }
        c = coefficient(idx3);
        z = exponent(idx3);
        return true;
    }
    
    template <typename T>
    void Cache<T>::print(std::ostream& o) const
    {
        table().print(o);
        o << std::endl;
        helper().print(o);
        o << std::endl;
        for (T i = 0; i < helper().size(); ++i) {
            o << power(i) << " ";
        }
        o << std::endl;
    }
    
    template <typename T>
    void Cache<T>::print(std::ostream& o, size_t a, size_t x, size_t b, size_t y, size_t c, size_t z) const
    {
        std::cout << "EQUATION - " << a << "^" << x << " + " << b << "^" << y << " = " << c << "^" << z << std::endl;
    }
}

#endif
