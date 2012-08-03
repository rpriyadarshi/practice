//
//  main.cpp
//  Permutation
//
//  Created by Rohit Priyadarshi on 9/4/11.
//  Copyright 2011 VirtualSamaj. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

class Permutation
{
public:
    typedef std::vector<std::string > Buffer;
    
public:
    Permutation(const std::string& str): m_data(str) {}
    const std::string& data() const { return m_data; }
    const Buffer& buffer() const { return m_buffer; }
    
    void operator()() { permute(); }
    
private:
    std::string& data() { return m_data; }
    Buffer& buffer() { return m_buffer; }
    void permute () {
    }
    void permuteOne (const char c, std::string& str) {
    }
    
private:
    std::string m_data;
    Buffer m_buffer;
};

std::ostream& operator<<(std::ostream& o, const Permutation& perm) {
    Permutation::Buffer::const_iterator iter;
    for (iter = perm.buffer().begin(); iter != perm.buffer().end(); ++iter) {
        const std::string& str = *iter;
        o << str << std::endl;
    }
    return o;
}

int main (int argc, const char * argv[])
{
    Permutation perm("abcd");
    perm();
    std::cout << perm;
    return 0;
}

