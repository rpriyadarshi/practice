//
//  main.cpp
//  StackOfPlates
//
//  Created by Rohit Priyadarshi on 12/30/12.
//  Copyright (c) 2012 Rohit Priyadarshi. All rights reserved.
//
// Imagine a (literal) stack of plates. If the stack gets too high,
// it might topple. Therefore, in real life, we would likely start
// a new stack when the previous stack exceeds some threshold.
// Implement a data structure SetOfStacks that mimics this. SetOfStacks
// should be composed of several stacks, and should create a new stack
// once the previous one exceeds capacity. SetOfStacks.push() and
// SetOfStacks.pop() should behave identically to a single stack
// (that is, pop() should return the same values as it would if there
// were just a single stack).
// FOLLOW UP
// Implement a function popAt(int index) which performs a pop operation
// on a specific sub-stack.

#include <iostream>

template <typename T>
class Stack {
public:
    Stack(int size)
    : _begin(new T[size]), _end(_begin + size - 1), _current(_end), _full(false), _empty(true) {}
    ~Stack() { delete _begin; }
    
    void push(T v) {
        *_current = v;
        _full = _current == _begin;
        if (_current > _begin)
            --_current;
    }
    T pop() {
        T v = *_current;
        _empty = _current == _end;
        if (_current < _end)
            ++_current;
        return v;
    }
    bool full() { return _full;; }
    bool empty() { return _empty; }
    
private:
    T* _begin;
    T* _end;
    T* _current;
    bool _full;
    bool _empty;
};

template<typename T>
class SetOfStacks {
public:
    SetOfStacks(int size, int maxStacks)
    : _stackSize(size), _maxStacks(maxStacks), _allocated(0), _stacks(new Stack<T>*[size]) {
        AddStack();
    }
    ~SetOfStacks() {
        for (int i = 0; i < _allocated; ++i) {
            delete _stacks[i];
        }
        delete _stacks;
    }
    void push(T v) {
        if (_stacks[_allocated - 1]->full())
            AddStack();
        _stacks[_allocated - 1]->push(v);
    }
    
    T pop() {
        T v = _stacks[_allocated - 1]->pop();
        if (_allocated > 0 && _stacks[_allocated - 1]->empty()) {
            delete _stacks[_allocated - 1];
            --_allocated;
        }
        return v;
    }
    
    T popAt(int idx) {
        idx = idx == _allocated < idx ? _allocated : idx;
        T v = _stacks[idx]->pop();
        return v;
    }
    
    void AddStack() {
        if (_allocated < _maxStacks) {
            _stacks[_allocated] = new Stack<T>(_stackSize);
            ++_allocated;
        } else {
            // increase stack collection
        }
    }
    
private:
    int _stackSize;
    int _maxStacks;
    int _allocated;
    Stack<T>** _stacks;
};

int main(int argc, const char * argv[])
{
    const int size = 10;
    
    Stack<int> s(size);
    for (int i = 0; i < size; ++i) {
        s.push(i + size);
    }
    for (int i = 0; i < size; ++i) {
        std::cout << s.pop() << std::endl;
    }
    std::cout << std::endl;
    
    SetOfStacks<int> s1(size, size);
    for (int i = 0; i < size*size; ++i) {
        s1.push(i + size);
    }
    for (int i = 0; i < size*size; ++i) {
        std::cout << s1.pop() << std::endl;
    }

    return 0;
}

