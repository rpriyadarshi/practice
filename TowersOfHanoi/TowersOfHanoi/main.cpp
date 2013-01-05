//
//  main.cpp
//  TowersOfHanoi
//
//  Created by Rohit Priyadarshi on 12/31/12.
//  Copyright (c) 2012 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>

template <typename T>
class Stack {
public:
    explicit Stack(int size)
    : _begin(new T[size]), _end(_begin + size - 1), _current(_end + 1) {
        memset(_begin, 0, sizeof(T*)*size);
    }
    ~Stack() { delete _begin; }
    
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
    void print(std::ostream& o) {
        T* p = _begin;
        while (p <= _end) {
            o << *p << " ";
            ++p;
        }
        o << std::endl;
    }

private:
    T* _begin;
    T* _end;
    T* _current;
};

template <typename T>
class TowersOfHanoi {
public:
    TowersOfHanoi(int size)
    : _sa(size), _sb(size), _sc(size), _size(size) { initialize(); }
    ~TowersOfHanoi() {}
    
    void initialize() {
        for (int i = 0; i < _size; ++i) {
            _sa.push(_size - i);
        }
    }

    void transfer() {
        transfer(_sa, _sb, _sc, _size-1);
    }
    void transfer(Stack<T>& a, Stack<T>& b, Stack<T>& c, int depth) {
        --depth;
        if (depth == 0) {
            transfer(a, c, b);
            transfer(a, b, c);
            transfer(b, a, c);
        } else {
            transfer(a, c, b, depth);
            transfer(a, b, c);
            transfer(b, a, c, depth);
        }
    }
    void transfer(Stack<T>& a, Stack<T>& b, Stack<T>& c) {
        c.push(a.pop());
    }
    void print(std::ostream& o) {
        _sa.print(o);
        _sb.print(o);
        _sc.print(o);
        o << std::endl;
    }
    
private:
    Stack<T> _sa;
    Stack<T> _sb;
    Stack<T> _sc;
    int _size;
};

int main(int argc, const char * argv[])
{
    TowersOfHanoi<int> t(100);
    t.transfer();
    t.print(std::cout);
    return 0;
}

