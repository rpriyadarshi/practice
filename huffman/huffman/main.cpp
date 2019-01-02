//
//  main.cpp
//  huffman
//
//  Created by Rohit Priyadarshi on 12/31/18.
//  Copyright © 2018 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <fstream>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
class HNode;

////////////////////////////////////////////////////////////////////////////////
typedef std::vector<HNode*> HNodeVec;
typedef std::queue<HNode*> HNodeQueue;
typedef std::stack<HNode*> HNodeStack;
typedef std::list<HNode*> HNodeList;

////////////////////////////////////////////////////////////////////////////////
class HNode {
public:
    explicit HNode(unsigned long w) : m_weight(w), m_depth(0), m_parent(nullptr), m_right(nullptr), m_left(nullptr) {}
    HNode(HNode* l, HNode* r);
    ~HNode() {}
    
public:
    unsigned long getWeight() const { return m_weight; }
    unsigned long getDepth() const { return m_depth; }
    const HNode* getParent() const { return m_parent; }
    const HNode* getRight() const { return m_right; }
    const HNode* getLeft() const { return m_left; }

public:
    unsigned long getWeight() { return m_weight; }
    unsigned long getDepth() { return m_depth; }
    HNode* getParent() { return m_parent; }
    HNode* getRight() { return m_right; }
    HNode* getLeft() { return m_left; }
    void setWeight(unsigned long w) { m_weight = w; }
    void setDepth(unsigned long d) { m_depth = d; }
    void setParent(HNode* n) { m_parent = n; }
    void setRight(HNode* n) { m_right = n; }
    void setLeft(HNode* n) { m_left = n; }

public:
    unsigned long m_weight;
    unsigned long m_depth;
    HNode* m_parent;
    HNode* m_right;
    HNode* m_left;
};

////////////////////////////////////////////////////////////////////////////////
struct {
    bool operator()(HNode* n1, HNode* n2) {
        return n1->getWeight() < n2->getWeight();
    }
} NNodeCmp;

////////////////////////////////////////////////////////////////////////////////
inline HNode::HNode(HNode* l, HNode* r) : m_weight(0), m_depth(0) {
    if (l) {
        setLeft(l);
        l->setParent(this);
        setWeight(getWeight() + l->getWeight());
    }
    if (r) {
        setRight(r);
        r->setParent(this);
        setWeight(getWeight() + r->getWeight());
    }
}

////////////////////////////////////////////////////////////////////////////////
class Huffman {
public:
    Huffman() : m_items(0), m_root(nullptr) {}
    ~Huffman();
    
public:
    bool readSize(std::ifstream& ifstr);
    bool readSymbols(std::ifstream& ifstr);
    bool read(const std::string& filename);
    
public:
    HNode* createNode(HNode* n1, HNode* n2);
    
public:
    void computeCode();
    void computeLength();
    void compute();

public:
    void dumpTree(std::ostream& o);
    void dumpCache(std::ostream& o);
    void dump(std::ostream& o);

private:
    int m_items;
    HNode* m_root;
    unsigned long m_minDepth;
    unsigned long m_maxDepth;

    HNodeVec m_cache;
    HNodeList m_q1;
    HNodeList m_q2;
};

////////////////////////////////////////////////////////////////////////////////
inline Huffman::~Huffman() {
    for (auto& c : m_cache) {
        delete c;
    }
}

inline bool Huffman::readSize(std::ifstream& ifstr) {
    std::string line;
    std::getline(ifstr, line);
    if (! ifstr.good()) {
        return false;
    }
    std::stringstream istr(line);
    istr >> m_items;
    return true;
}

inline bool Huffman::readSymbols(std::ifstream& ifstr) {
    std::string line;
    std::getline(ifstr, line);
    if (! ifstr.good()) {
        return false;
    }
    std::stringstream istr(line);
    unsigned long weight = 0;
    istr >> weight;
    
    HNode* n = new HNode(weight);
    m_cache.push_back(n);
    
    return true;
}

inline bool Huffman::read(const std::string& filename) {
    std::ifstream ifstr(filename);
    if (! ifstr.good()) {
        std::cout << "ERROR: Could not read \"" << filename << "\"" << std::endl;
        return false;
    }
    // Get graph size
    if (! readSize(ifstr)) {
        return false;
    }
    
    while (readSymbols(ifstr));
    return false;
}

inline HNode* Huffman::createNode(HNode* l, HNode* r) {
    HNode* n = new HNode(l, r);
    m_cache.push_back(n);
    m_q2.push_back(n);
    
    return n;
}

inline void Huffman::computeCode() {
    std::sort(m_cache.begin(), m_cache.end(), NNodeCmp);
    for (auto& c : m_cache) {
        m_q1.push_back(c);
    }
    
    HNode* n1 = nullptr;
    HNode* n2 = nullptr;
    
    while (! m_q1.empty() || ! m_q2.empty()) {
        n1 = n2 = nullptr;
        if (m_q1.empty()) {
            if (m_q2.empty()) { // Cannot come here since both queues must be empty
            } else { // n2
                n2 = m_q2.front();
                m_q2.pop_front();
                if (! m_q2.empty()) { // Take from same q2 queue
                    n1 = m_q2.front();
                    m_q2.pop_front();
                } else { // Finished
                }
            }
        } else { // n1
            if (m_q2.empty()) {
                n1 = m_q1.front();
                m_q1.pop_front();
                if (! m_q1.empty()) { // Take from same q1 queue
                    n2 = m_q1.front();
                    m_q1.pop_front();
                } else { // Finished
                }
            } else { // n1, n2
                n1 = m_q1.front();
                m_q1.pop_front();
                
                n2 = m_q2.front();
                m_q2.pop_front();
                
                // Second level compares
                HNode* nm = nullptr;
                if (m_q1.empty()) { // no more choices to be made
                } else {
                    nm = m_q1.front();
                    m_q1.pop_front();
                    
                    unsigned long w2 = n2->getWeight();
                    unsigned long wm = nm->getWeight();
                    
                    if (w2 > wm) { // nm is a better candidate
                        m_q2.push_front(n2);
                        n2 = nm;
                    } else { // return nm back
                        m_q1.push_front(nm);
                    }
                }
            }
        }
        
        if (n1 && n2) {
            createNode(n1, n2);
        }
    }
    m_root = n1 ? n1 : n2;
}

inline void Huffman::computeLength() {
    m_minDepth = std::numeric_limits<unsigned long>::max();
    m_maxDepth = std::numeric_limits<unsigned long>::min();
    
    HNodeStack stack;
    stack.push(m_root);
    while (!stack.empty()) {
        HNode* n = stack.top();
        HNode* r = n->getRight();
        HNode* l = n->getLeft();
        stack.pop();
        
        // Body
        unsigned long depth = n->getDepth();
        if (l == nullptr && r == nullptr) {
            m_minDepth = std::min(m_minDepth, depth);
            m_maxDepth = std::max(m_maxDepth, depth);
        }
        
        depth++;
        if (r) {
            stack.push(r);
            r->setDepth(depth);
        }
        if (l) {
            stack.push(l);
            l->setDepth(depth);
        }
    }
}

inline void Huffman::compute() {
    computeCode();
    computeLength();
}

inline void Huffman::dumpTree(std::ostream& o) {
    HNodeStack stack;
    stack.push(m_root);
    while (!stack.empty()) {
        HNode* n = stack.top();
        HNode* r = n->getRight();
        HNode* l = n->getLeft();
        stack.pop();
        
        // Body
        o << n->getWeight() << "[" << n->getDepth() << "]" << std::endl;
        
        if (r) {
            stack.push(r);
        }
        if (l) {
            stack.push(l);
        }
    }
}

inline void Huffman::dumpCache(std::ostream& o) {
    for (auto& w : m_cache) {
        std::cout << w->getWeight() << std::endl;
    }
}

inline void Huffman::dump(std::ostream& o) {
//    dumpCache(o);
//    dumpTree(o);
    o << "Min-depth=" << m_minDepth << std::endl;
    o << "Max-depth=" << m_maxDepth << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    // max = 19, min = 9
    std::string filename("/Users/rohit/Documents/Development/practice/huffman/huffman.txt");
    // max = 3, min = 2
//    std::string filename("/Users/rohit/Documents/Development/practice/huffman/huffman2.txt");
    Huffman h;
    h.read(filename);
    h.compute();
    h.dump(std::cout);
    return 0;
}
