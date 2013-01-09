//
//  main.cpp
//  SortStack
//
//  Created by Rohit Priyadarshi on 1/7/13.
//  Copyright (c) 2013 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>

template <typename T>
class Stack {
public:
    explicit Stack(size_t size)
    : _begin(new T[size]), _end(_begin + size - 1), _current(_end + 1) {}
    ~Stack() {}
    
    void push(T v) {
        if (_current > _begin)
            --_current;
        *_current = v;
    }
    T pop() {
        T v = *_current;
        *_current = 0;
        if (_current <= _end)
            ++_current;
        return v;
    }
    T peek() {
        return *_current;
    }
    bool isEmpty() {
        return _end - _current;
    }
    size_t size() {
        return _end - _begin + 1;
    }
    
private:
    T* _begin;
    T* _end;
    T* _current;
};

template <typename T>
class BubbleSort {
public:
    explicit BubbleSort(size_t size)
    : _primary(size), _secondary(size) {}
    ~BubbleSort() {}
    void push(T v) {
        _primary.push(v);
    }
    T pop() {
        return _primary.pop();
    }
    T peek() {
        return _primary.peek();
    }
    bool isEmpty() {
        return _primary.isEmpty();
    }
    void sort() {
        size_t size = _primary.size();
        for (int i = 0; i < size; ++i) {
            T v1 = _primary.pop();
            for (int j = 1; j < size; ++j) {
                T v2 = _primary.pop();
                if (v1 > v2) {
                    _secondary.push(v1);
                    v1 = v2;
                } else {
                    _secondary.push(v2);
                }
            }
            _secondary.push(v1);
            
            for (int i = 0; i < size; ++i) {
                _primary.push(_secondary.pop());
            }
        }
    }
    
private:
    Stack<T> _primary;
    Stack<T> _secondary;
};

int main(int argc, const char * argv[])
{
    const int size = 10;
    BubbleSort<int> s(size);
    for (int i = 0; i < size; ++i) {
        s.push(size - i);
    }
    s.sort();
    for (int i = 0; i < size; ++i) {
        std::cout << s.peek() << " " << s.pop() << " " << s.peek() << " " << s.isEmpty() << std::endl;
    }

    return 0;
}

