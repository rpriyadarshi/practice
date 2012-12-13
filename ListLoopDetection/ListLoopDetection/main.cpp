//
//  main.cpp
//  ListLoopDetection
//
//  Created by Rohit Priyadarshi on 12/12/12.
//  Copyright (c) 2012 Rohit Priyadarshi. All rights reserved.
//
//  Given a circular linked list, implement an algorithm which returns node at
//  the begin- ning of the loop.
//  DEFINITION
//  Circular linked list: A (corrupt) linked list in which a node’s next pointer
//  points to an earlier node, so as to make a loop in the linked list.
//  EXAMPLE
//  input: A -> B -> C -> D -> E -> C [the same C as earlier]
//  output: C
// 
#include <iostream>

template <typename T>
class Node {
public:
    Node(T d) : _next(0), _data(d) {}
    ~Node() {}
    
    Node* next() { return _next; }
    T data() { return _data; }
    void next(Node* k) { _next = k; }
    void data(T d) { _data = d; }
    
private:
    Node* _next;
    T _data;
};

template <typename T>
class List {
public:
    List() : _head(0) {}
    ~List() {}
    
    Node<T>* head() { return _head; }
    void head(Node<T>* k) { _head = k; }
    Node<T>* prepend(T d) {
        Node<T>* k = create(d);
        return prepend(k);
    }
    Node<T>* prepend(Node<T>* k) {
        Node<T>* h = head();
        if (h) {
            k->next(h);
        }
        head(k);
        return k;
    }
    Node<T>* create(T d) {
        Node<T>* k = new Node<T>(d);
        return k;
    }
    void remove(Node<T>* k) {
        Node<T>* h = head();
        if (h == k) {   
            head(h->next());
        } else {
            Node<T>* p = h;
            Node<T>* n = h->next();
            while (n) {
                if (n == k) {
                    p->next(k);
                    break;
                }
                p = n;
                n = n->next();
            }
        }
    }
    std::ostream& dump(std::ostream& o) {
        Node<T>* k = head();
        while (k) {
            o << k << "->(" << k->data() << ")" << std::endl;
            k = k->next();
        }
        return o;
    }
    
private:
    Node<T>* _head;
};

int main(int argc, const char * argv[])
{
    List<int> l;
    for (int i = 0; i < 10; ++i) {
        l.prepend(i);
    }
    l.dump(std::cout);
    return 0;
}

