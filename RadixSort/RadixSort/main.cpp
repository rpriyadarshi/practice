//
//  main.cpp
//  RadixSort
//
//  Created by Rohit Priyadarshi on 6/18/11.
//  Copyright 2011 VirtualSamaj. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>

class RadixSort
{
public:
    RadixSort(std::vector<int>& v)
    : m_data(v), m_radix(), m_exponent(1)
    {
        for (int i = 0; i < 10; ++i) {
            std::vector<int> v;
            std::pair<int, std::vector<int> > p(i, v);
            radix().insert(p);
        }
    }
    ~RadixSort() {}

public: // FUnctions
    const std::vector<int>& data() const { return m_data; }
    int exponent() const { return m_exponent; }
    std::ostream& operator<<(std::ostream& o) 
    {
#if 0
        std::map<int, std::vector<int> >::const_iterator miter;
        o << "Radix:" << std::endl;
        for (miter = radix().begin(); miter != radix().end(); ++miter) {
            o << (*miter).first << " ";
            std::vector<int>::const_iterator viter;
            o << "Radix Data: ";
            const std::vector<int>& v = (*miter).second;
            for (viter = v.begin(); viter != v.end(); ++viter) {
                o << *viter << " ";
            }
            o << std::endl;
        }
        o << std::endl;
#endif
        std::vector<int>::const_iterator viter;
        o << "Data: ";
        for (viter = data().begin(); viter != data().end(); ++viter) {
            o << *viter << " ";
        }
        o << std::endl;
        return o;
    }
    
    int digit(int n, int e)
    {
        return (n/e)%10;
    }
    
    int incr_exponent() 
    {
        int e = exponent();
        exponent(e*10);
        return exponent();
    }
    
    int decr_exponent() 
    {
        int e = exponent();
        exponent(e/10);
        return exponent();
    }

    
    void sort()
    {
        std::map<int, std::vector<int> > m1(radix());
        std::map<int, std::vector<int> > m2(radix());
        
        std::vector<int>::const_iterator iter;
        std::map<int, std::vector<int> >::const_iterator miter;

        int e = exponent();
        for (iter = data().begin(); iter != data().end(); ++iter) {
            int n = *iter;
            int i = digit(n, e);
            m1[i].push_back(n);
        }
        e = incr_exponent();
        bool hasSomeNonZero = true;
        while (hasSomeNonZero) {
            hasSomeNonZero = false;
            for (miter = m1.begin(); miter != m1.end(); ++miter) {
                int k = (*miter).first;
                std::vector<int>::const_iterator viter;
                const std::vector<int>& v = (*miter).second;
                for (viter = v.begin(); viter != v.end(); ++viter) {
                    int n = *viter;
                    int i = digit(n, e);
                    m2[i].push_back(n);
                    if (k > 0)
                    {
                        hasSomeNonZero = true;
                    }
                }
            }
            e = incr_exponent();
            m1 = m2;
            m2 = radix();
        }
        
        radix() = m1;
        data() = m1[0];
    }
    
private: // Functions
    const std::map<int, std::vector<int> >& radix() const { return m_radix; }
    std::vector<int>& data() { return m_data; }
    std::map<int, std::vector<int> >& radix() { return m_radix; }
    void exponent(int e) { m_exponent = e; }
    
private: // Data
    std::vector<int>& m_data;
    std::map<int, std::vector<int> > m_radix;
    int m_exponent;
};

std::ostream& operator<<(std::ostream& o, RadixSort& r) 
{
    return r.operator<<(o);
}

int main (int argc, const char * argv[])
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(5);
    v.push_back(1098);
    v.push_back(13);
    v.push_back(234);
    v.push_back(321);
    v.push_back(13);
    v.push_back(431);
    v.push_back(2441);
    v.push_back(223);
    v.push_back(0243);
    v.push_back(253);
    v.push_back(1);
    
    RadixSort r(v);
    
    std::cout << r << std::endl;
    r.sort();
    std::cout << r << std::endl;
#if 0
    for (int i = 0; i < 9; ++i) {
        std::cout << r.digit(239721028, r.exponent());
        //std::cout << r.exponent() << std::endl;
        r.incr_exponent();
    }
    std::cout << std::endl;
    r.decr_exponent();
    for (int i = 0; i < 9; ++i) {
        std::cout << r.digit(239721028, r.exponent());
        //std::cout << r.exponent() << std::endl;
        r.decr_exponent();
    }
#endif
    std::cout << std::endl;
    return 0;
}

