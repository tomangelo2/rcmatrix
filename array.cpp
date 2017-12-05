#include "array.h"

CArray::CArray(int h, int w, double v, double f): m_col(w), m_row(h)
{
    int i = 0;
    A = new double*[h];
    try
    {
        for(i = 0; i < h; i++)
        {
            A[i] = new double[w];
        }
    }catch(...)
    {
        while(i > 0)
        {
            delete A[--i];
        }
        delete A;
        throw;
    }
    for (i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if(i == j)
            {
                A[i][i] = v;
            }
            else
            {
                A[i][j] = f;
            }
        }
    }
}

CArray::CArray(std::fstream &f)
{
    int i;
    if(!f.is_open())
    {
        throw file_not_open();
    }


    f >> this->m_row >> this->m_col;

    try
    {
        A = new double*[m_row];
    }catch(...)
    {
        throw bad_alloc();
    }
    try
    {
        for(i = 0; i < m_row; i++)
        {
            A[i] = new double[m_col];
        }
    }catch(...)
    {
        while(i > 0)
        {
            delete A[--i];
        }
        delete A;
        throw bad_alloc();
    }


    if(this->m_row <= 0 || this->m_row <= 0)
    {
        delete A;
        throw WrongDim();
    }

    for(int i = 0; i < this->m_row; i++)
    {
        for(int j = 0; i < this->m_col; i++)
        {
            if(f.good())
                f >> A[i][j];
            else
            {
                delete A;
                throw file_error();
            }
        }
    }
}

CArray::CArray()
{

}

CArray::~CArray()
{

}

