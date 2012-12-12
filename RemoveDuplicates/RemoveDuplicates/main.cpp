//
//  main.cpp
//  RemoveDuplicates
//
//  Created by Rohit Priyadarshi on 4/5/11.
//  Copyright 2011 VirtualSamaj. All rights reserved.
//

#include <iostream>
#include <list>
#include <map>

class elem
{
public:
    elem(int d): m_data(d) {};
    ~elem() {};
    
    int data() { 
        return m_data; 
    }
    std::ostream& dump(std::ostream& o) 
    { 
        return o << data(); 
    }
    
private:
    int m_data;
};

inline std::ostream& operator<<(std::ostream& o, elem& e) 
{
    return e.dump(o);
}

int main (int argc, const char * argv[])
{
    srand(0);
    std::list<elem> l;
    
    for (int i = 0; i < 1000; i++)
    {
        elem e(rand() % 100);
        l.push_back(e);
    }

    std::cout << "list size " << l.size() << std::endl;
    std::map<int, elem> m;
    std::list<elem>::iterator liter;
    for (liter = l.begin(); liter != l.end(); ++liter)
    {
        elem& e = *liter;
        std::cout << e << " ";
        std::map<int, elem>::iterator miter = m.find(e.data());
        if (miter != m.end())
        {
            l.erase(liter);
        }
        else
        {
            std::pair<int, elem> p(e.data(), e);
            m.insert(p);
        }
    }

    std::cout << std::endl;
    std::cout << "list size " << l.size() << std::endl;
    for (liter = l.begin(); liter != l.end(); ++liter)
    {
        elem& e = *liter;
        std::cout << e << " ";
    }
    std::cout << std::endl;
    return 0;
}

