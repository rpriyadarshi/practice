//
//  node.h
//  AVLTree
//
//  Created by Rohit Priyadarshi on 7/10/11.
//  Copyright 2011 VirtualSamaj. All rights reserved.
//

namespace DS {
    template <class T> T min(T t1, T t2) { return t1 < t2 ? t1 : t2; }
    template <class T> T max(T t1, T t2) { return t1 > t2 ? t1 : t2; }
    
    template <class T> class Node
    {
    public:
        explicit Node(T d) 
        : m_data(d), m_count(1), m_height(0), 
        m_parent(0), m_left(0), m_right(0) {}
        ~Node() {}
        
        const T data() const { return m_data; }
        int count() const { return m_count; }
        int height() const { return m_height; }
        const Node* parent() const { return m_parent; }
        const Node* left() const { return m_left; }
        const Node* right() const { return m_right; }
        
        T data() { return m_data; }
        int count() { return m_count; }
        int height() { return m_height; }
        Node* parent() { return m_parent; }
        Node* left() { return m_left; }
        Node* right() { return m_right; }
        
        void data(T d) { m_data = d; }
        void count(int c) { m_count = c; }
        void height(int h) { m_height = h; }
        void parent(Node* n) { m_parent = n; }
        void left(Node* n);
        void right(Node* n);
        
        bool is_leaf() const;
        void update_height();
        bool avl_check_balance() const;
        int avl_calculate_balance() const;
        void incrCount() { count(count() + 1); }
        void decrCount() { count(count() - 1); }
        void incrHeight() { height(height() + 1); }
        void decrHeight() { height(height() - 1); }
        
        std::ostream&  print(std::ostream& o) const;

    private:
        T m_data;
        int m_count;
        int m_height;
        Node* m_parent;
        Node* m_left;
        Node* m_right;
    };
    
    template <class T> inline bool 
    operator==(const Node<T>& n1, const Node<T>& n2) { return n1.data() == n2.data(); }
    template <class T> inline bool 
    operator==(T v, const Node<T>& n) { return v == n.data(); }
    template <class T> inline bool 
    operator==(const Node<T>& n, T v) { return n.data() == v; }
    
    template <class T> inline bool 
    operator<(const Node<T>& n1, const Node<T>& n2) { return n1.data() < n2.data(); }
    template <class T> inline bool 
    operator<(T v, const Node<T>& n) { return v < n.data(); }
    template <class T> inline bool 
    operator<(const Node<T>& n, T v) { return n.data() < v; }
    
    template <class T> inline bool 
    operator>(const Node<T>& n1, const Node<T>& n2) { return n1.data() > n2.data(); }
    template <class T> inline bool 
    operator>(T v, const Node<T>& n) { return v > n.data(); }
    template <class T> inline bool 
    operator>(const Node<T>& n, T v) { return n.data() > v; }
    
    template <class T> inline std::ostream& 
    operator<<(std::ostream& o, const Node<T>& n) { return n.print(o); }
    
    template <class T> inline void 
    Node<T>::left(Node<T>* n) 
    { 
        m_left = n; 
        if (left())
        {
            left()->parent(this);
        }
    }
    
    template <class T> inline void 
    Node<T>::right(Node<T>* n) 
    { 
        m_right = n; 
        if (right())
        {
            right()->parent(this);
        }
    }
    
    template <class T> inline inline bool 
    Node<T>::is_leaf() const
    {
        const Node* l = left();
        const Node* r = right();
        return (l == 0 && r == 0);
    }
    
    template <class T> inline inline void
    Node<T>::update_height()
    {
        int h = 0;
        Node* l = left();
        Node* r = right();
        if (l != 0)
        {
            if (r != 0)
            {
                h = max<int>(l->height(), r->height());
                height(++h);                
            }
            else
            {
                h = l->height();
                height(++h);                
            }
        }
        else
        {
            if (r != 0)
            {
                h = r->height();
                height(++h);                
            }
            else
            {
                height(0);                
            }
        }
    }
    
    template <class T> inline bool 
    Node<T>::avl_check_balance() const
    {
        int balance = avl_calculate_balance();
        return (balance < 2 && balance > -2);
    }
    
    template <class T> inline int 
    Node<T>::avl_calculate_balance() const
    {
        int balance = 0;
        const Node* l = left();
        const Node* r = right();
        if (l != 0) {
            if (r != 0) {
                balance = r->height() - l->height();
            }
            else
            {
                balance = -height();
            }
        }
        else
        {
            if (r != 0) {
                balance = height();
            }
        }
        return balance;
    }
    
    template <class T> inline std::ostream&
    Node<T>::print(std::ostream& o) const
    {
        o << "\"" 
        << data() 
        << "[" 
        << count() 
        << ":" 
        << height() 
        << ":"
        << avl_calculate_balance()
        << ":"
        << (avl_check_balance() ? "T" : "F")
        << "]\"";
        return o; 
    }
    
}
