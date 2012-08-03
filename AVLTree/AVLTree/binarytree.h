//
//  binarytree.h
//  AVLTree
//
//  Created by Rohit Priyadarshi on 7/10/11.
//  Copyright 2011 VirtualSamaj. All rights reserved.
//

namespace DS {

    template <class T>
    class BinaryTree
    {
    public:
        typedef std::stack<const Node<T>* > NStack;
        
    public:
        BinaryTree() : m_root(0) {}
        ~BinaryTree() { deleteTree(); }
        
        const Node<T>* root() const { return m_root; }
        Node<T>* insert(T v);
        
        const Node<T>* find(T i) const;
        Node<T>* update_height(Node<T>* n);
        
        // DFS Operations
        NStack& dfs_init(NStack& s) const;
        const Node<T>* dfs_next(NStack& s) const;
        
        // AVL Operations
        Node<T>* avl_insert(T v);
        
        std::ostream&  print(std::ostream& o) const ;
        Node<T>* root() { return m_root; }
        void root(Node<T>* r) { m_root = r; }
        
    private:
        
        Node<T>* createNode(T d) { return new Node<T>(d); }
        
        void deleteTree() {}
        
        // AVL Operations
        Node<T>* avl_single_rotate_left(Node<T>* n);
        Node<T>* avl_single_rotate_right(Node<T>* n);
        Node<T>* avl_double_rotate_left_right(Node<T>* n);
        Node<T>* avl_double_rotate_right_left(Node<T>* n);
        Node<T>* avl_rotate(Node<T>* n);
        void avl_rebalance(Node<T>* n);

    private:
        Node<T>* m_root;
    };
    
    template <class T> inline std::ostream& 
    operator<<(std::ostream& o, const BinaryTree<T>& t) { return t.print(o); }
    
    template <class T> inline Node<T>*
    BinaryTree<T>::insert(T v)
    {
        Node<T>* n = root();
        if (n == 0)
        {
            root(createNode(v));
            n = root();
        }
        else
        {
            while (n) {
                if (*n == v) {
                    n->incrCount();
                    break;
                }
                else
                {
                    if (*n > v) {
                        Node<T>* l = n->left();
                        if (l == 0)
                        {
                            n->left(createNode(v));
                            n = n->left();
                            break;
                        }
                        n = l;
                    }
                    else
                    {
                        if (*n < v) {
                            Node<T>* r = n->right();
                            if (r == 0)
                            {
                                n->right(createNode(v));
                                n = n->right();
                                break;
                            }
                            n = r;
                        }
                    }
                }
            }
        }

        return n;
    }
    
    template <class T> inline const Node<T>*
    BinaryTree<T>::find(T v) const
    {
        const Node<T>* f = 0;
        const Node<T>* n = root();
        while (n) {
            if (*n == v) {
                f = n;
                break;
            }
            else
            {
                if (*n > v) {
                    n = n->left();
                }
                else
                {
                    if (*n < v) {
                        n = n->right();
                    }
                }
            }
        }
        return f;
    }
    
    template <class T> inline Node<T>*
    BinaryTree<T>::update_height(Node<T>* n)
    {
        if (n != 0)
        {
            Node<T>* p = n->parent();
            int h = n->height();
            while (p != 0) {
                p->height(max<int>(p->height(), ++h));
                p = p->parent();
            }
        }
        return n;
    }
    
    template <class T> inline typename BinaryTree<T>::NStack& 
    BinaryTree<T>::dfs_init(NStack& s) const
    {
        const Node<T>* n = root();
        if (n != 0)
        {
            s.push(n);
        }
        return s;
    }
    
    template <class T> inline const Node<T>* 
    BinaryTree<T>::dfs_next(NStack& s) const
    {
        const Node<T>* n = 0;
        if (!s.empty())
        {
            n = s.top();
            const Node<T>* l = n->left();
            const Node<T>* r = n->right();
            s.pop();
            if (r != 0)
            {
                s.push(r);
            }
            if (l != 0)
            {
                s.push(l);
            }
        }
        return n;
    }
    
    template <class T> inline void
    BinaryTree<T>::avl_rebalance(Node<T>* n)
    {
        if (n != 0)
        {
            Node<T>* pp = root();
            Node<T>* p = n->parent();
            if (!n->avl_check_balance())
            {
                n = avl_rotate(n);
                pp = n;
                p = n->parent();
            }
            while (p != 0) {
                p->update_height();
                if (!p->avl_check_balance())
                {
                    p = avl_rotate(p);
                }
                pp = p; // save root
                p = p->parent();
            }
            root(pp);
        }
    }
    
    template <class T> inline Node<T>*
    BinaryTree<T>::avl_insert(T v)
    {
        Node<T>* n = insert(v);
        avl_rebalance(n);
        return n;
    }
    
    template <class T> inline Node<T>* 
    BinaryTree<T>::avl_single_rotate_left(Node<T>* n)
    {
        Node<T>* t = 0;
        if (n != 0)
        {
            Node<T>* p = n->parent();
            Node<T>* l = n->left();
            if (l != 0)
            {
                Node<T>* lr = l->right();
                n->left(lr);
                if (lr != 0)
                {
                    lr->parent(n);
                }
                n->update_height();
                
                l->right(n);
                n->parent(l);
                l->parent(p);
                l->update_height();
                t = l;
            }
            if (p != 0)
            {
                Node<T>* pl = p->left();
                Node<T>* pr = p->right();
                if (pl == n)
                {
                    p->left(t);
                }
                else
                {
                    if (pr == n)
                    {
                        p->right(t);
                    }
                }
                p->update_height();
            }
        }
        
        return t;
    }
    
    template <class T> inline Node<T>* 
    BinaryTree<T>::avl_single_rotate_right(Node<T>* n)
    {
        Node<T>* t = 0;
        if (n != 0)
        {
            Node<T>* p = n->parent();
            Node<T>* r = n->right();
            if (r != 0)
            {
                Node<T>* rl = r->left();
                n->right(rl);
                if (rl != 0)
                {
                    rl->parent(n);
                }
                n->update_height();

                r->left(n);
                n->parent(r);
                r->parent(p);
                r->update_height();
                t = r;
            }
            if (p != 0)
            {
                Node<T>* pl = p->left();
                Node<T>* pr = p->right();
                if (pl == n)
                {
                    p->left(t);
                }
                else
                {
                    if (pr == n)
                    {
                        p->right(t);
                    }
                }
                p->update_height();
            }
        }
        
        return t;
    }
    
    template <class T> inline Node<T>* 
    BinaryTree<T>::avl_double_rotate_left_right(Node<T>* n)
    {
        Node<T>* t = 0;
        if (n != 0)
        {
            Node<T>* l = n->left();
            if (l != 0)
            {
                l = avl_single_rotate_right(l);
                n->left(l);
                l->parent(n);
                n->update_height();
                t = avl_single_rotate_left(n);
            }
        }
        return t;
    }
    
    template <class T> inline Node<T>* 
    BinaryTree<T>::avl_double_rotate_right_left(Node<T>* n)
    {
        Node<T>* t = 0;
        if (n != 0)
        {
            Node<T>* r = n->right();
            if (r != 0)
            {
                r = avl_single_rotate_left(r);
                n->right(r);
                r->parent(n);
                n->update_height();
                t = avl_single_rotate_right(n);
            }
        }
        return t;
    }
    
    template <class T> inline Node<T>* 
    BinaryTree<T>::avl_rotate(Node<T>* n)
    {
        Node<T>* t = 0;
        if (n != 0) {
            Node<T>* l = 0;
            Node<T>* r = 0;
            int nbal = n->avl_calculate_balance();
            if (nbal < 0) { // left
                l = n->left();
                int lbal = l->avl_calculate_balance();
                if (lbal < 0) { // left
                    t = avl_single_rotate_left(n);
                }
                else
                {
                    if (lbal > 0) { // right
                        t = avl_double_rotate_left_right(n);
                    }
                }
            }
            else
            {
                if (nbal > 0) { // right
                    r = n->right();
                    int rbal = r->avl_calculate_balance();
                    if (rbal > 0) { // right
                        t = avl_single_rotate_right(n);
                    }
                    else
                    {
                        if (rbal < 0) { // left
                            t = avl_double_rotate_right_left(n);
                        }
                    }
                }
            }
        }
        return t;
    }
    
    template <class T> inline std::ostream&  
    BinaryTree<T>::print(std::ostream& o) const 
    { 
        o << "digraph BinaryTree {" << std::endl;
        NStack s;
        dfs_init(s);
        const Node<T>* c = dfs_next(s);
        const Node<T>* n = 0;
        while (c) {
            n = dfs_next(s);
            
            c->print(o);
            if (c->is_leaf())
            {
                o << ";" << std::endl;
                if (n != 0)
                {
                    const Node<T>* p = n->parent();
                    if (p != 0)
                    {
                        p->print(o);
                    }
                    o << " -> ";
                }
            }
            else
            {
                o << " -> ";
            }
            o << std::flush;
            
            c = n;
        }
        o << "}" << std::endl;
        return o; 
    }
    
}

