//
//  main.cpp
//  MinStack
//
//  Created by Rohit Priyadarshi on 12/30/12.
//  Copyright (c) 2012 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>

template <class T>
class Stack {
public:
    Stack(T* b, T* e, T* m)
    : _begin(b), _end(e), _current(e), _min(m), _currMin(m) {}
    ~Stack() {}
    
    void push(T v) {
        *_current = v;
        if (_currMin < _min) {
            T pm = *(_currMin + 1);
            if (pm < v) *_currMin = pm;
            else *_currMin = v;
        } else {
            *_currMin = v;
        }
        if (_current > _begin) {
            --_current;
            --_currMin;
        }
    }
    T pop() {
        T v = *_current;
        if (_current < _end) {
            ++_current;
            ++_currMin;
        }
        return v;
    }
    T min() { return *_currMin; }
    
private:
    T* _begin;
    T* _end;
    T* _current;
    T* _min;
    T* _currMin;
};

int main(int argc, const char * argv[])
{
    const int size = 10;
    int a[size];
    int m[size];
    memset(a, INT64_MIN, sizeof(a));
    memset(m, INT64_MAX, sizeof(m));
    Stack<int> s(a, a + size - 1, m + size - 1);
    
    for (int i = 0; i < size/2; ++i) {
        s.push(size - i);
    }
    for (int i = 0; i < size/2; ++i) {
        s.push(i);
    }
    
    for (int i = 0; i < size; ++i) {
        std::cout << s.min() << " " << s.pop() << std::endl;
    }
    return 0;
}

