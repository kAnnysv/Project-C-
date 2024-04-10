#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>
#include <cstdio>
#include <utility>


class S21Matrix {
    public:

    int GetRows();
    int GetCols();
    void SetRows(int rows);
    void SetColumns(int cols);
    double** getMatrix();

    S21Matrix();  // Default constructor
    S21Matrix(int rows, int columns);
    S21Matrix(const S21Matrix &other);
    S21Matrix(S21Matrix &&other);
    ~S21Matrix();  // Destructor

    void operator=(const S21Matrix &other);
    void operator=(S21Matrix &&other);
    bool operator==(const S21Matrix &other);
    S21Matrix operator+(const S21Matrix &other);
    void operator+=(const S21Matrix &other);
    void operator-=(const S21Matrix &other);
    S21Matrix operator-(const S21Matrix &other);
    S21Matrix operator*(int a);
    S21Matrix operator*(const S21Matrix &other);
    void operator*=(double a);
    void operator*=(const S21Matrix &other);
    double &operator()(int i, int j);

    void printMatrix();
    void feelMatrix(int num);

    bool EqMatrix(const S21Matrix &other);
    void SumMatrix(const S21Matrix &other);
    void SubMatrix(const S21Matrix &other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix &other);

    S21Matrix Transpose();
    double Determinant();
    S21Matrix CalcComplements();
    S21Matrix InverseMatrix();




    private:

    int rows_, cols_;  // Rows and columns
    double** matrix_; 
    void deleteMatrix();
    void matrix_reduction(int row, int col, const S21Matrix &tmp);


};








































#endif  // S21_MATRIX_OOP_H
