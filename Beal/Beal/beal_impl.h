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
    BigInt::BigInt()
    {
        memset(this, 0, sizeof(*this));
    }
    
    size_t BigInt::size() const
    {
        return IntToShort * BigIntSize;
    }
    
    unsigned short& BigInt::operator[](size_t idx)
    {
        return data(idx);
    }
    
    unsigned short& BigInt::data(size_t idx)
    {
        size_t i = idx / BigIntSize;
        size_t j = idx % BigIntSize;
        return _data[j]._sint[i];
    }
    
    const unsigned short& BigInt::data(size_t idx) const
    {
        size_t i = idx / BigIntSize;
        size_t j = idx % BigIntSize;
        return _data[j]._sint[i];
    }
    
    BigInt& BigInt::mulhu(BigInt& u, BigInt& v)
    {
        BigInt& w = *this;
        unsigned int k, t;
        size_t s = size();
        
        for (size_t j = 0; j < s; ++j) {
            k = 0;
            for (size_t i = 0; i < s; ++i) {
                t = u[i] * v[j] + w[i + j] + k;
                w[i + j] = t;
                k = t >> ShortSize;
            }
            w[j + s] = k;
        }
        return *this;
    }
    
    void BigInt::print(std::ostream& o) const
    {
        for (int i = 0; i < size(); ++i) {
            o << data(i) << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < BigIntSize; ++i) {
            o << _data[i]._uint << " ";
        }
        std::cout << std::endl;
    }
    
    template <typename T>
    Vector<T>::Vector(size_t s)
    : _size(s), _data(new T[s])
    {
        fill();
    }
    
    template <typename T>
    Vector<T>::~Vector()
    {
        delete _data;
    }
    
    template <typename T>
    void Vector<T>::fill()
    {
        linear();
    }
    
    template <typename T>
    void Vector<T>::linear()
    {
        for (size_t i = 0; i < size(); ++i) {
            data(i) = i;
        }
    }

    template <typename T>
    void Vector<T>::print(std::ostream& o) const
    {
        for (size_t i = 0; i < size(); ++i) {
            o << data(i) << " ";
        }
        o << std::endl;
    }
    
    template <typename T>
    T& Vector<T>::operator[](size_t i) const
    {
        return data(i);
    }
    
    template <typename T>
    std::ostream& operator<<(std::ostream& o, Vector<T>& v)
    {
        v.print(o);
        return o;
    }
    
    template <typename T>
    Array<T>::Array(size_t x, size_t y)
    : _xSize(x), _ySize(y), _data(new T[x * y])
    {
        fill();
    }
    
    template <typename T>
    Array<T>::~Array()
    {
        delete _data;
    }
    
    template <typename T>
    T& Array<T>::data(size_t x, size_t y) const
    {
        return data(index(x, y));
    }
    
    template <typename T>
    size_t Array<T>::index(size_t x, size_t y) const
    {
        return x + y * xSize();
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
            data(x, 0) = i++;
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
    T& Array<T>::operator[](size_t i) const
    {
        return data(i);
    }

    template <typename T>
    T& Array<T>::operator()(size_t x, size_t y) const
    {
        return data(x, y);
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& o, Array<T>& a)
    {
        a.print(o);
        return o;
    }
    
    template <typename T>
    Cache<T>::Cache(size_t x, size_t y)
    : _table(x, y), _helper(x * y)
    {
    }
    
    template <typename T>
    Cache<T>::~Cache()
    {
    }
    
    template <typename T>
    T& Cache<T>::power(size_t i)
    {
        return table()[helper()[i]];
    }
    
    template <typename T>
    const T& Cache<T>::power(size_t i) const
    {
        return table()[helper()[i]];
    }
    
    template <typename T>
    T& Cache<T>::power(size_t x, size_t y)
    {
        return power(table().index(x, y));
    }
    
    template <typename T>
    const T& Cache<T>::power(size_t x, size_t y) const
    {
        return power(table().index(x, y));
    }
    
    template <typename T>
    bool Cache<T>::checkSort(size_t i, size_t j) const
    {
        error(false);
        size_t p = power(i);
        for (size_t l = i + 1; l < j; ++l) {
            size_t c = power(l);
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
        Vector<T> idx(idx_size);
        size_t i = i1;
        size_t j = j1;
        size_t k = 0;
        while (i < i2 && j < j2) {
            size_t idx_i = helper(i);
            size_t idx_j = helper(j);
            size_t v1 = table(idx_i);
            size_t v2 = table(idx_j);
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
            size_t p = power(i);
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
    size_t Cache<T>::coefficient(size_t idx) const
    {
        return idx % table().xSize();
    }
    
    template <typename T>
    size_t Cache<T>::exponent(size_t idx) const
    {
        return idx / table().xSize();
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
        for (size_t i = 0; i < helper().size(); ++i) {
            o << power(i) << " ";
        }
        o << std::endl;
    }
    
    template <typename T>
    void Cache<T>::print(std::ostream& o, size_t a, size_t x, size_t b, size_t y, size_t c, size_t z) const
    {
        std::cout << "EQUATION - " << a << "^" << x << " + " << b << "^" << y << " = " << c << "^" << z << std::endl;
    }
    
    template <typename T>
    std::ostream& operator<<(std::ostream& o, Cache<T>& c)
    {
        c.print(o);
        return o;
    }
}

#endif
