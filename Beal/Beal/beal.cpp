//
//  beal.cpp
//  Beal
//
//  Created by Rohit Priyadarshi on 6/11/13.
//  Copyright (c) 2013 Rohit Priyadarshi. All rights reserved.
//

#include "beal.h"

#define _DEBUG

namespace Beal {
    Vector::Vector(size_t s)
    : _size(s), _data(new size_t[s])
    {
        fill();
    }
    
    Vector::~Vector()
    {
        delete _data;
    }
    
    void Vector::fill()
    {
        linear();
    }
    
    void Vector::linear()
    {
        for (size_t i = 0; i < size(); ++i) {
            data(i) = i;
        }
    }

    void Vector::print(std::ostream& o) const
    {
        for (size_t i = 0; i < size(); ++i) {
            o << data(i) << " ";
        }
        o << std::endl;
    }
    
    size_t& Vector::operator[](size_t i) const
    {
        return data(i);
    }
    
    std::ostream& operator<<(std::ostream& o, Vector& v)
    {
        v.print(o);
        return o;
    }
    
    Array::Array(size_t x, size_t y)
    : _xSize(x), _ySize(y), _data(new size_t[x * y])
    {
        fill();
    }
    
    Array::~Array()
    {
        delete _data;
    }
    
    size_t& Array::data(size_t x, size_t y) const
    {
        return data(index(x, y));
    }
    
    size_t Array::index(size_t x, size_t y) const
    {
        return x + y * xSize();
    }
    
    void Array::fill()
    {
        linear();
        for (size_t y = 1; y < ySize(); ++y) {
            power(y);
        }
    }
    
    void Array::linear()
    {
        size_t i = 1;
        for (size_t x = 0; x < xSize(); ++x) {
            data(x, 0) = i++;
        }
    }
    
    void Array::power(size_t y)
    {
        for (size_t x = 0; x < xSize(); ++x) {
            data(x, y) = data(x, y - 1) * data(x, 0);
        }
    }
    
    void Array::print(std::ostream& o) const
    {
        for (size_t y = 0; y < ySize(); ++y) {
            for (size_t x = 0; x < xSize(); ++x) {
                o << data(x, y) << " ";
            }
            o << std::endl;
        }
    }
    
    size_t& Array::operator[](size_t i) const
    {
        return data(i);
    }

    size_t& Array::operator()(size_t x, size_t y) const
    {
        return data(x, y);
    }

    std::ostream& operator<<(std::ostream& o, Array& a)
    {
        a.print(o);
        return o;
    }
    
    Cache::Cache(size_t x, size_t y)
    : _table(x, y), _helper(x * y)
    {
    }
    
    Cache::~Cache()
    {
    }
    
    size_t& Cache::power(size_t i)
    {
        return table()[helper()[i]];
    }
    
    const size_t& Cache::power(size_t i) const
    {
        return table()[helper()[i]];
    }
    
    size_t& Cache::power(size_t x, size_t y)
    {
        return power(table().index(x, y));
    }
    
    const size_t& Cache::power(size_t x, size_t y) const
    {
        return power(table().index(x, y));
    }
    
    bool Cache::checkSort(size_t i, size_t j) const
    {
        size_t p = power(i);
        for (size_t l = i + 1; l < j; ++l) {
            size_t c = power(l);
            if (c < p) {
                std::cout << "ERROR @ " << l << " " << p << " " << c << std::endl;
                return false;
            }
            p = c;
        }
        return true;
    }
    
    bool Cache::checkSort() const
    {
        size_t l_max = table().xSize() * table().ySize();
        return checkSort(0, l_max);
    }
    
    void Cache::sort()
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
        std::cout << std::endl;
    }

    void Cache::merge(size_t i1, size_t i2, size_t j1, size_t j2)
    {
#ifdef _DEBUG
        std::cout << "BINS - " << i1 << " " << i2 << " " << j1 << " " << j2 << std::endl;
        checkSort(i1, i2);
        checkSort(j1, j2);
#endif
        size_t idx_size = i2 - i1 + j2 - j1;
        Vector idx(idx_size);
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
    
    size_t Cache::find(size_t v) const
    {
        size_t l_min = 0;
        size_t l_max = helper().size();
        while (l_max - l_min) {
            size_t w = (l_max - l_min) / 2;
            size_t i = l_min + w;
            size_t p = power(i);
            if (v < p) {
                l_max = i;
            } else if (v > p) {
                l_min = i;
            } else {
                return i;
            }
        }
        return SIZE_T_MAX;
    }
    
    bool Cache::calculate(size_t a, size_t x, size_t b, size_t y) const
    {
        size_t v1 = table().data(a - 1, x - 1);
        size_t v2 = table().data(b - 1, y - 1);
        size_t v3 = v1 + v2;
        size_t idx = find(v3);
#ifdef _DEBUG
        size_t idx1 = find(v1);
        size_t idx2 = find(v2);
        std::cout << v1 << " " << v2 << " " << v3 << " " << idx1 << " " << idx2 << " " << idx << std::endl;
#endif
        return true;
    }
    
    void Cache::print(std::ostream& o) const
    {
#ifdef _DEBUG
        table().print(o);
        o << std::endl;
        helper().print(o);
        o << std::endl;
#endif
        for (size_t i = 0; i < helper().size(); ++i) {
            o << power(i) << " ";
        }
        o << std::endl;
        o << (checkSort() ? "OK" : "ERROR");
        o << std::endl;
    }
    
    std::ostream& operator<<(std::ostream& o, Cache& c)
    {
        c.print(o);
        return o;
    }
}
