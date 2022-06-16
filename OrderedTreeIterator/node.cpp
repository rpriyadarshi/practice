#pragma once

namespace nonstd
{

template <typename _D>
void node<_D>::print(const std::string& header, size_t indent, bool shallow) const
{
    std::cout << header;
    for (int i = 0; i < indent; i++)
    {
        std::cout << " ";
    }
    std::cout << m_data;
    if (shallow) 
    {
        return;
    }
    std::cout << std::endl;
    indent += 2; // indent increment
    for (auto c : get_children()) 
    {
        auto ptr = c.get();
        ptr->print(header, indent, shallow);
    }
}

};
