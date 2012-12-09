//
//  main.cpp
//  rotateMatrix
//
//  Created by Rohit Priyadarshi on 12/2/12.
//  Copyright (c) 2012 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <iomanip>

class matrix {
public:
    matrix(int n) : _size(n) { create_matrix(); }
    matrix() { delete_matrix(); }
        
    int* operator[](int index) {
        return data()[index];
    }
    void rotate() {
        int cache[4];
        memset(cache, 0, sizeof(cache));
        
        int x_max = size();
        int y_max = size();
        
        for (int y = 0; y < y_max; ++y) {
            int y_up = y;
            int y_dn = y_max - y - 1;
            if (y_up > y_dn)
                break;
            
            for (int x = 0; x < x_max; ++x) {
                int x_up = x;
                int x_dn = x_max - x - 1;
                if (x_up > x_dn)
                    break;

                cache[0] = data()[y_up][x_up];
                cache[1] = data()[x_up][y_dn];
                cache[2] = data()[y_dn][x_dn];
                cache[3] = data()[x_dn][y_up];
                
                data()[y_up][x_up] = cache[1];
                data()[x_up][y_dn] = cache[2];
                data()[y_dn][x_dn] = cache[3];
                data()[x_dn][y_up] = cache[0];
            }
        }
    }
    
    void print(std::ostream& o) {
        const int WIDTH = 2;
        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                o << std::setw(WIDTH) << data()[i][j] << " ";
            }
            o << std::endl;
        }
    }
    
    bool test() {
        set_test_values();
        return check_test_values();
    }
    
    void set_test_values() {
        int v = 0;
        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                data()[i][j] = v++;
            }
        }
    }
    
    bool check_test_values() {
        int v = 0;
        for (int i = 0; i < size(); ++i) {
            for (int j = 0; j < size(); ++j) {
                if (data()[i][j] != v++) {
                    return false;
                }
            }
        }
        return true;
    }
    
private:
    int size() { return _size; }
    int ** data() { return _data; }
    
    void create_matrix() {
        _data = new int*[size()];
        for (int i = 0; i < size(); ++i) {
            _data[i] = new int[size()];
        }
    }
    
    void delete_matrix() {
        for (int i = 0; i < size(); ++i) {
            delete data()[i];
        }
        delete data();
    }
    
private:
    int _size;
    int ** _data;
};

int main(int argc, const char * argv[])
{
    matrix m(10);
    bool status = m.test();
    if (! status) {
        std::cout << "Matrix setup failed!" << std::endl;
    } else {
        std::cout << "Matrix setup successful!" << std::endl;
    }
    m.print(std::cout);
    m.rotate();
    std::cout << std::endl;
    m.print(std::cout);
    m.rotate();
    m.rotate();
    m.rotate();
    status = m.check_test_values();
    if (! status) {
        std::cout << "Matrix check failed!" << std::endl;
    } else {
        std::cout << "Matrix check successful!" << std::endl;
    }
    return 0;
}

