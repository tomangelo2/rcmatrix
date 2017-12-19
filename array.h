#ifndef CARRAY_H
#define CARRAY_H

#include <fstream>

class CArray
{
public:
    CArray(int h, int w, double v, double f);
    CArray(int h, int w, double** mat);
    CArray(std::fstream &f);
    CArray();
    ~CArray();

    CArray* detach();


    double** A;
    int m_col, m_row; //wymiary
    unsigned int n; //ilość wystąpień
};

/*Wyjątki*/
class IndexOutOfRange{};
class WrongDim{};
class bad_alloc{};
class null_as_argument{};
class file_error{};
class file_not_open{};

#endif // CARRAY_H
