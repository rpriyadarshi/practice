//
//  main.cpp
//  QueueFromStack
//
//  Created by Rohit Priyadarshi on 1/3/13.
//  Copyright (c) 2013 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>

template <typename T>
class Stack {
public:
    explicit Stack(int size)
    : _begin(new T[size]), _end(_begin + size - 1), _current(_end + 1) {}
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
    size_t elements() {
        return _end - _current + 1;
    }
    void print(std::ostream& o) {
        T* p = _end;
        while (p >= _begin) {
            o << *p << " ";
            --p;
        }
        o << std::endl;
    }
    
private:
    T* _begin;
    T* _end;
    T* _current;
};

template <typename T>
class Queue {
public:
    explicit Queue(int size)
    : _push(size), _pop(size) {}
    Queue() {}
    
    void queue(T v) {
        size_t size = _pop.elements();
        for (int i = 0; i < size; ++i) {
            _push.push(_pop.pop());
        }
        _push.push(v);
    }
    T dequeue() {
        size_t size = _push.elements();
        for (int i = 0; i < size; ++i) {
            _pop.push(_push.pop());
        }
        return _pop.pop();
    }
    T peek() {
        if (_push.elements() && _pop.elements()) {
            return T(0);
        } else if (_push.elements()) {
            return _push.peek();
        } else if (_pop.elements()) {
            return _pop.peek();
        }
        return T(0);
    }
    size_t elements() {
        return _push.elements() + _pop.elements();
    }

public:
    Stack<T> _push;
    Stack<T> _pop;
};

int main(int argc, const char * argv[])
{
    const int size = 10;
#if 0
    Stack<int> s(size);
    for (int i = 0; i < size; ++i) {
        s.push(size - i);
        std::cout << s.peek() << " " << s.elements() << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << s.pop() << " " << s.elements() << std::endl;
    }
#else
    Queue<int> q(size);
    for (int i = 0; i < size; ++i) {
        q.queue(size - i);
        std::cout << q.peek() << " " << q.elements() << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << q.dequeue() << " " << q.elements() << std::endl;
    }
#endif
    return 0;
}

