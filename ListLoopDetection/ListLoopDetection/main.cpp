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
    
    std::ostream& dump(std::ostream& o) {
        o << this << "->(" << data() << ")" << std::endl;
        return o;
    }
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
    Node<T>* corrupt(int l) {
        int i = 0;
        Node<T>* k = head();
        Node<T>* k1 = 0;
        Node<T>* k2 = 0;
        while (k) {
            if (i == l) k1 = k;
            k2 = k;
            ++i;
            k = k->next();
        }
        k2->next(k1);
        return k1;
    }
    Node<T>* find_loop_ordered() {
        Node<T>* k = head();
        Node<T>* p = k;
        Node<T>* n = k;
        while (k) {
            n = k->next();
            if ((p < k && k > n) || (p > k && k < n)) {
                break;
            }
            p = k;
            k = n;
        }
        return n;
    }
    Node<T>* find_loop_runner() {
        Node<T>* k1 = head();
        Node<T>* k2 = head()->next();
        while (k2) {
            k1 = k1->next();
            if (k2->next()) {
                k2 = k2->next()->next();
            }
            if (k1 == k2) {
                break;
            }
        }
        return k2;
    }
    void fix_loop() {
        Node<T>* k = head();
        Node<T>* p = k;
        Node<T>* n = k;
        while (k) {
            n = k->next();
            if ((p < k && k > n) || (p > k && k < n)) {
                break;
            }
            p = k;
            k = n;
        }
        k->next(0);
    }
    std::ostream& dump(std::ostream& o) {
        Node<T>* k = head();
        while (k) {
            k->dump(o);
            k = k->next();
        }
        return o;
    }
    
private:
    Node<T>* _head;
};

int main(int argc, const char * argv[])
{
    const int size = 10;
    List<int> l;
    for (int i = 0; i < size; ++i) {
        l.prepend(i);
    }
    for (int i = 0; i < size - 1; ++i) {
        l.corrupt(i)->dump(std::cout);
        //l.find_loop_ordered()->dump(std::cout);
        l.find_loop_runner()->dump(std::cout);
        std::cout << std::endl;
        l.fix_loop();
    }
    l.dump(std::cout);
    return 0;
}

