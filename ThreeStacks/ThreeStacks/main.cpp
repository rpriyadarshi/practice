//
//  main.cpp
//  ThreeStacks
//
//  Created by Rohit Priyadarshi on 12/23/12.
//  Copyright (c) 2012 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>

template <typename T>
class Stack {
public:
    Stack(T* begin, T* end)
    : _begin(begin), _end(end), _current(end) {}
    ~Stack() {}
    
    size_t size() {
        return (_begin < _end ? _end - _begin : _begin - _end) + 1;
    }
    bool push(T v, T* _min, T* _max) {
        *_current = v;
        bool overflow = _current == _begin;
        if (_begin < _end) { // Natural Array
            if (_current > _begin && _current <= _end) {
                --_current;
            }
        } else { // Circular Array
            if ((_current > _begin && _current <= _max) ||
                (_current > _min && _current <= _end)) {
                --_current;
            } else if (_current == _min) {
                _current = _max;
            }
        }
        
        return overflow;
    }
    T pop(T* _min, T* _max) {
        T v = *_current;
        if (_begin < _end) { // Natural Array
            if (_current >= _begin && _current < _end) {
                ++_current;
            }
        } else { // Circular Array
            if ((_current >= _begin && _current < _max) ||
                (_current >= _min && _current < _end)) {
                ++_current;
            } else if (_current == _max) {
                _current = _min;
            }
        }
        
        return v;
    }
    
public:
    T* _begin;
    T* _end;
    T* _current;
};

template <typename T>
class NStacks {
public:
    NStacks(size_t size)
    : _size(size), _data(new T[_size]),
    _stack1(_data, _data + size/3 - 1),
    _stack2(_data + size/3, _data + 2 * size/3 - 1),
    _stack3(_data + 2 * size/3, _data + size - 1) {}
    ~NStacks() { delete _data; }
    
    T* data() const { return _data; }
    Stack<T>& stack1() { return _stack1; }
    Stack<T>& stack2() { return _stack2; }
    Stack<T>& stack3() { return _stack3; }
    
    size_t size1() { return _stack1.size(); }
    size_t size2() { return _stack2.size(); }
    size_t size3() { return _stack3.size(); }
    
    bool push1(T v) { return _stack1.push(v, _data, _data + _size - 1); }
    bool push2(T v) { return _stack2.push(v, _data, _data + _size - 1); }
    bool push3(T v) { return _stack3.push(v, _data, _data + _size - 1); }

    T pop1() { return _stack1.pop(_data, _data + _size - 1); }
    T pop2() { return _stack2.pop(_data, _data + _size - 1); }
    T pop3() { return _stack3.pop(_data, _data + _size - 1); }

    void calc_empty() {}
    void re_distribute() {}
    
public:
    size_t _size;
    T* _data;
    Stack<T> _stack1;
    Stack<T> _stack2;
    Stack<T> _stack3;
};

int main(int argc, const char * argv[])
{
    const size_t size = 30;
    NStacks<int> ns(size);
    memset(ns.data(), 0, size*sizeof(int*));
    
    for (int i = 0; i < ns.size1(); ++i) {
        ns.push1(i + 10);
    }
    for (int i = 0; i < ns.size2(); ++i) {
        ns.push2(i + 20);
    }
    for (int i = 0; i < ns.size3(); ++i) {
        ns.push3(i + 30);
    }
    
    for (int i = 0; i < ns.size1(); ++i) {
        std::cout << ns.pop1() << std::endl;
    }
    for (int i = 0; i < ns.size2(); ++i) {
        std::cout << ns.pop2() << std::endl;
    }
    for (int i = 0; i < ns.size3(); ++i) {
        std::cout << ns.pop3() << std::endl;
    }
    return 0;
}

