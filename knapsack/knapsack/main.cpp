//
//  main.cpp
//  knapsack
//
//  Created by Rohit Priyadarshi on 1/13/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

////////////////////////////////////////////////////////////////////////////////
class Item;

////////////////////////////////////////////////////////////////////////////////
typedef std::pair<size_t, size_t> ItemPair;
typedef std::vector<Item*> ItemsVec;
typedef std::unordered_map<int, size_t> ValueMap;
typedef std::unordered_map<int, ValueMap> ValueTable;

////////////////////////////////////////////////////////////////////////////////
class Item {
public: // Constructors/destructors
    Item(size_t val, int wt) : m_value(val), m_weight(wt) {}
    ~Item() {}
    
public:
    void dump(std::ostream& o);
    
public:
    size_t getValue() const { return m_value; }
    int getWeight() const { return m_weight; }

private:
    size_t m_value;
    int m_weight;
};

inline void Item::dump(std::ostream& o) {
    o << m_value << " " << m_weight;
}

////////////////////////////////////////////////////////////////////////////////
class Knapsack {
public: // Constructors/destructors
    Knapsack() : m_size(0) {}
    ~Knapsack() {}
    
public:
    size_t compute();
    size_t value(int i);
    int weight(int i);
    size_t at(const int i, const int x);
    void at(const int i, const int x, size_t val);

public:
    bool readSize(std::ifstream& ifstr);
    bool readItem(std::ifstream& ifstr);
    bool read(const std::string& filename);
    
public:
    void dumpItems(std::ostream& o);
    void dumpTable(std::ostream& o);

private:
    size_t m_size;
    ItemsVec m_cache;
    ValueTable m_table;
};

////////////////////////////////////////////////////////////////////////////////
inline bool Knapsack::readSize(std::ifstream& ifstr) {
    std::string line;
    std::getline(ifstr, line);
    if (! ifstr.good()) {
        return false;
    }
    std::stringstream istr(line);
    int items;
    istr >> m_size >> items;
//    m_items.resize(items);
    Item* itm = new Item(0, 0);
    m_cache.push_back(itm);
    return true;
}

inline bool Knapsack::readItem(std::ifstream& ifstr) {
    std::string line;
    std::getline(ifstr, line);
    if (! ifstr.good()) {
        return false;
    }
    std::stringstream istr(line);
    int val, wt;
    istr >> val >> wt;
    Item* itm = new Item(val, wt);
    m_cache.push_back(itm);
    return true;
}

inline bool Knapsack::read(const std::string& filename) {
    std::ifstream ifstr(filename);
    if (! ifstr.good()) {
        std::cout << "ERROR: Could not read \"" << filename << "\"" << std::endl;
        return false;
    }
    // Get graph size
    if (! readSize(ifstr)) {
        return false;
    }
    
    while (readItem(ifstr));
    return false;
}

inline void Knapsack::dumpItems(std::ostream& o) {
    for (auto item : m_cache) {
        item->dump(o);
        o << std::endl;
    }
    o << std::endl;
}

inline void Knapsack::dumpTable(std::ostream& o) {
    for (int x = static_cast<int>(m_size); x >= 0; x--) {
        for (int i = 0; i < m_cache.size(); i++) {
            o << at(i, x) << " ";
        }
        o << std::endl;
    }
    o << std::endl;
}

inline size_t Knapsack::value(int i) {
    Item* ptr = m_cache[i];
    if (ptr) {
        return ptr->getValue();
    }
    return 0;
}

inline int Knapsack::weight(int i) {
    Item* ptr = m_cache[i];
    if (ptr) {
        return ptr->getWeight();
    }
    return 0;
}

inline size_t Knapsack::at(const int i, const int x) {
    return m_table[i % 2][x]; // m_table[i][x];
}

inline void Knapsack::at(const int i, const int x, size_t val) {
    m_table[i % 2][x] = val; // m_table[i][x] = val;
}

inline size_t Knapsack::compute() {
    for (int i = 1; i < m_cache.size(); i++) {
        for (int x = 0; x <= m_size; x++) {
            // A[i, x] := max{A[i-1, x], A[i-1, x-wi] + vi};
            size_t vi = value(i);
            int wi = weight(i);
            size_t v = 0;
            if (wi > x) {
                v = at(i - 1, x);
            } else {
                size_t a = at(i - 1, x);
                size_t b = at(i - 1, x - wi);
                v = std::max(a, b + vi);
            }
            at(i, x, v);
        }
    }
    // return A[m_cache.size()-1, m_size]
    size_t res = at(static_cast<int>(m_cache.size()) - 1, static_cast<int>(m_size));
    return res;
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    // 8
//    std::string filename("/Users/rohit/Documents/Development/practice/knapsack/knapsack_book.txt");
    // 4
//    std::string filename("/Users/rohit/Documents/Development/practice/knapsack/input_random_1_4_4.txt");
    // 6
//    std::string filename("/Users/rohit/Documents/Development/practice/knapsack/input_random_2_4_4.txt");
    // 14
//    std::string filename("/Users/rohit/Documents/Development/practice/knapsack/input_random_5_10_10.txt");
    // 19
//    std::string filename("/Users/rohit/Documents/Development/practice/knapsack/input_random_6_10_10.txt");
    // 147
//    std::string filename("/Users/rohit/Documents/Development/practice/knapsack/input_random_10_100_10.txt");
    // 5399
//    std::string filename("/Users/rohit/Documents/Development/practice/knapsack/input_random_21_1000_100.txt");
    // 49957183
//    std::string filename("/Users/rohit/Documents/Development/practice/knapsack/input_random_44_2000000_2000.txt");
    // 2493893
//    std::string filename("/Users/rohit/Documents/Development/practice/knapsack/knapsack1.txt");
    //4243395
    std::string filename("/Users/rohit/Documents/Development/practice/knapsack/knapsack_big.txt");

    Knapsack k;
    k.read(filename);
//    k.dumpItems(std::cout);
    
    size_t v = k.compute();
    
//    k.dumpTable(std::cout);
    std::cout << v << std::endl;
    return 0;
}
