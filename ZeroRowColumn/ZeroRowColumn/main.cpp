//
//  main.cpp
//  ZeroRowColumn
//
//  Created by Rohit Priyadarshi on 12/8/12.
//  Copyright (c) 2012 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <iomanip>

class Matrix {
public:
    Matrix(int row, int col) : _row(row), _col(col), _data(NULL) { create_data(); }
    ~Matrix() { delete_data(); }
    
    int row() { return _row; }
    int col() { return _col; }
    int** data() { return _data; }
    int* row_data() { return _row_data; }
    int* col_data() { return _col_data; }
    
    int* operator[](int i) { return data()[i]; }
    
    void transfer() {
        for (int i = 0; i < row(); ++i) {
            for (int j = 0; j < col(); ++j) {
                if (! data()[i][j]) {
                    row_data()[i] = 0;
                    col_data()[j] = 0;
                }
            }
        }
        for (int i = 0; i < row(); ++i) {
            for (int j = 0; j < col(); ++j) {
                int r = row_data()[i];
                int c = col_data()[j];
                if (! r || ! c) {
                    data()[i][j] = 0;
                }
            }
        }
    }
    
    bool test() {
        setup_test();
        return check_test();
    }
    
    void setup_test() {
        int v = 0;
        for (int i = 0; i < row(); ++i) {
            for (int j = 0; j < col(); ++j) {
                data()[i][j] = ++v;
            }
        }
    }
    
    bool check_test() {
        int v = 0;
        for (int i = 0; i < row(); ++i) {
            for (int j = 0; j < col(); ++j) {
                if (data()[i][j] != ++v) {
                    return false;
                }
            }
        }
        return true;
    }

    void create_data() {
        _row_data = new int[row()];
        _col_data = new int[col()];
        _data = new int*[row()];
        for (int i = 0; i < row(); ++i) {
            _data[i] = new int[col()];
            _row_data[i] = 1;
        }
        for (int j = 0; j < col(); ++j) {
            _col_data[j] = 1;
        }
    }
    
    void delete_data() {
        for (int i = 0; i < row(); ++i) {
            delete _data[i];
        }
        delete _row_data;
        delete _col_data;
    }

    void print(std::ostream& o) {
        o << std::setw(4) << 0;
        for (int j = 0; j < col(); ++j) {
            o << std::setw(4) << col_data()[j];
        }
        o << std::endl;
        for (int i = 0; i < row(); ++i) {
            o << std::setw(4) << row_data()[i];
            for (int j = 0; j < col(); ++j) {
                o << std::setw(4) << data()[i][j];
            }
            o << std::endl;
        }
        o << std::endl;
    }
    
private:
    int     _row;
    int     _col;
    int**   _data;
    int*    _row_data;
    int*    _col_data;
};

int main(int argc, const char * argv[])
{
    const int r = 15;
    const int c = 10;
    Matrix m(r, c);
    bool status = m.test();
    if (! status) {
        std::cout << "Matrix setup failed!" << std::endl;
    } else {
        std::cout << "Matrix setup successful!" << std::endl;        
    }
    m[2][4] = 0;
    m[5][7] = 0;
    m.transfer();
    m.print(std::cout);
    return 0;
}

