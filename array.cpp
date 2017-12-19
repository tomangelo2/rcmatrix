#include "array.h"

CArray::CArray(int h, int w, double v, double f): m_col(w), m_row(h)
{
    int i = 0;
    A = new double*[m_row];
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
            delete[] A[--i];
        }
        delete[] A;
        throw;
    }
    for (i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_col; j++)
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
    n = 1;
}

CArray::CArray(int h, int w, double** mat): m_col(w), m_row(h)
{
    int i = 0;
    A = new double*[m_row];
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
            delete[] A[--i];
        }
        delete[] A;
        throw;
    }
    for (i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            A[i][j] = mat[i][j];
        }
    }
    n = 1;
}

CArray::CArray(std::fstream &f)
{
    int i;
    if(!f.is_open())
    {
        throw file_not_open();
    }


    f >> this->m_row >> this->m_col;

    if(this->m_row <= 0 || this->m_col <= 0)
    {
        throw WrongDim();
    }

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
            delete[] A[--i];
        }
        delete[] A;
        throw bad_alloc();
    }

    for(int i = 0; i < this->m_row; i++)
    {
        for(int j = 0; j < this->m_col; j++)
        {
            if(f.good())
                f >> A[i][j];
            else
            {
                for(int i = 0; i < m_row; i++)
                {
                    delete[] A[i];
                }
                delete[] A;
                throw file_error();
            }
        }
    }
    n = 1;
}

CArray::CArray()
{

}

CArray::~CArray()
{
    for(int i = 0; i < m_row; i++)
    {
        delete[] A[i];
    }
    delete[] A;
}

CArray* CArray::detach()
{
    if(n==1)
      return this;
    CArray* t=new CArray(m_row, m_col, A);
    n--;
    return t;
}
