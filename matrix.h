#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

#include "array.h"

class CMatrix
{
public:
    //Konstruktor tworzący nową macierz
    //h - wysokość, w - szerokość, v - wartość na przekątnej, f - wartość pozostałych pól macierzy
    CMatrix(int w, int h, double v = 0.0f, double f = 0.0f);
    //Konstruktor kopiujący macierz
    CMatrix(const CMatrix& m);
    //Konstruktor tworzący macierz z wczytanego pliku
    CMatrix(std::fstream &f);
    //Pusty konstruktor
    CMatrix();
    ~CMatrix();

    class Cref;

    /*Metody*/
    void check (int i, int j);

    int getRows() const;
    int getColumns() const;

    double read(int col, int row) const;
    void write(int col, int row, double val);

    /*operatory*/
    //Przypisanie macierzy jako klasy
    CMatrix operator=(CMatrix mat);
    //Zapisanie wartości do macierzy
    //CMatrix operator=(double num);
    //Operator przypisujący do wyjścia
    friend std::ostream& operator<<(std::ostream &os, CMatrix &matrix);
    //Mnożenie klasy macierzy
    CMatrix operator*(CMatrix mat);
    //Wybór elementu
    double* operator[](int i);
    //Cref operator[](int i);

private:
    CArray* array;
};
/*
class CMatrix::Cref
{
    friend class CMatrix;
    CMatrix& mat;
    int m_col, m_row;

public:
    Cref(CMatrix& matrix, int col);
    operator double();
    Cref& operator=(int num);
    Cref& operator=(Cref& ref);
};
*/
#endif // MATRIX_H
