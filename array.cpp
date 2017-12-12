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
            delete A[--i];
        }
        delete A;
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
}

CArray::CArray(std::fstream &f)
{
    int i;
    if(!f.is_open())
    {
        throw file_not_open();
    }


    f >> this->m_row >> this->m_col;

    if(this->m_row <= 0 || this->m_row <= 0)
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
            delete A[--i];
        }
        delete A;
        throw bad_alloc();
    }

    for(int i = 0; i < this->m_row; i++)
    {
        for(int j = 0; j < this->m_col; j++)
        {
            if(f.good())
                f >> A[i][j]; //tutaj się sypie
            //gdb - 3: A[i][j] = <error: Cannot access memory at address 0xabababab>
            //czyli coś jest nie tak z alokacją
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

