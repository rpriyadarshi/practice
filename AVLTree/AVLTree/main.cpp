//
//  main.cpp
//  BinaryTree
//
//  Created by Rohit Priyadarshi on 6/26/11.
//  Copyright 2011 VirtualSamaj. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "node.h"
#include "binarytree.h"

template <class T>
void example1(DS::BinaryTree<T>& t)
{
    t.insert(4);
    t.insert(2);
    t.insert(1);
    t.insert(3);
    t.insert(5);
    t.insert(6);
}

template <class T>
void example2(DS::BinaryTree<T>& t)
{
    t.insert_and_update_height(9);
    
    t.insert_and_update_height(8);
    t.insert_and_update_height(10);
    
    t.insert_and_update_height(7);
    t.insert_and_update_height(12);
    
    t.insert_and_update_height(6);
    t.insert_and_update_height(11);
    t.insert_and_update_height(28);
    
    t.insert_and_update_height(5);
    t.insert_and_update_height(20);
    t.insert_and_update_height(32);
    
    t.insert_and_update_height(4);
    t.insert_and_update_height(16);
    t.insert_and_update_height(24);
    t.insert_and_update_height(30);
    
    t.insert_and_update_height(3);
    t.insert_and_update_height(14);
    t.insert_and_update_height(18);
    t.insert_and_update_height(22);
    t.insert_and_update_height(26);
    t.insert_and_update_height(29);
    t.insert_and_update_height(31);
    
    t.insert_and_update_height(2);
    t.insert_and_update_height(13);
    t.insert_and_update_height(15);
    t.insert_and_update_height(17);
    t.insert_and_update_height(19);
    t.insert_and_update_height(21);
    t.insert_and_update_height(23);
    t.insert_and_update_height(25);
    t.insert_and_update_height(27);
    t.insert_and_update_height(1);
}

template <class T>
void example3(DS::BinaryTree<T>& t)
{
    t.insert_and_update_height(7);
    
    t.insert_and_update_height(4);
    t.insert_and_update_height(13);
    
    t.insert_and_update_height(2);
    t.insert_and_update_height(6);
    t.insert_and_update_height(11);
    t.insert_and_update_height(15);
    
    t.insert_and_update_height(1);
    t.insert_and_update_height(3);
    t.insert_and_update_height(5);
    t.insert_and_update_height(9);
    t.insert_and_update_height(12);
    t.insert_and_update_height(14);
    t.insert_and_update_height(16);
    
    t.insert_and_update_height(8);
    t.insert_and_update_height(10);
}

template <class T>
void example4(DS::BinaryTree<T>& t)
{
    t.avl_insert(3);
    t.avl_insert(2);
    t.avl_insert(1);
}

template <class T>
void example5(DS::BinaryTree<T>& t)
{
    t.avl_insert(1);
    t.avl_insert(2);
    t.avl_insert(3);
}

template <class T>
void example6(DS::BinaryTree<T>& t)
{
    t.avl_insert(4);
    t.avl_insert(2);
    t.avl_insert(3);
}

template <class T>
void example7(DS::BinaryTree<T>& t)
{
    t.avl_insert(2);
    t.avl_insert(4);
    t.avl_insert(3);
}

template <class T>
void exampleN(DS::BinaryTree<T>& t)
{
    t.avl_insert(3);
    t.avl_insert(2);
    t.avl_insert(1);
    t.avl_insert(4);
    t.avl_insert(5);
    t.avl_insert(6);
    t.avl_insert(7);
    t.avl_insert(16);
    t.avl_insert(15);
    t.avl_insert(14);
    t.avl_insert(13);
    t.avl_insert(12);
    t.avl_insert(11);
    t.avl_insert(10);
    t.avl_insert(8);
    t.avl_insert(9);
}

int main (int argc, const char * argv[])
{
    DS::BinaryTree<int> t;
//    example1(t);
//    example2(t);
//    example3(t);
//    example4(t);
//    example5(t);
//    example6(t);
//    example7(t);
    exampleN(t);
    
    // Test outputs
    std::cout << t << std::endl;
    
    // Out to file
    if (argc > 1)
    {
        std::ofstream of(argv[1]);
        of << t << std::endl;
    }
    
    std::vector<int> v;
    v.push_back(6);
    v.push_back(100);
    
    for (std::vector<int>::const_iterator itr = v.begin(); itr != v.end(); ++itr)
    {
        int i = (*itr);
        const DS::Node<int>* f = t.find(i);
        if (f != 0)
        {
            std::cout << "Found (" << i << "): " << *f << std::endl;
        }
        else
        {
            std::cout << "Not found (" << i << ") "<< std::endl;
        }

    }
    
    return 0;
}

