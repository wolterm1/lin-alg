#include <cmath>
#include <numeric>

#pragma once

namespace linAlg  {
    

    template <typename T>
    Matrix<T>::Matrix(const size_t &rows, const size_t &columns, const T& value)  {
        this->rows = rows;
        this->columns = columns;
        matrixData = new T[rows*columns];
        for(int i=0; i<rows; i++)  {
            for(int j=0; j<columns;j++)  {
                if(i==j)    {
                    (*this)(i,j) = value;
                } else {
                    (*this)(i,j) = value;
                }
            }
        }
    }


    template <typename T>
    Matrix<T>::Matrix(const size_t &rows, const size_t &columns)  {
        this->rows = rows;
        this->columns = columns;
        matrixData = new T[rows*columns];
        for(int i=0; i<rows; i++)  {
            for(int j=0; j<columns;j++)  {
                if(i==j)    {
                    (*this)(i,j) = 1;
                } else {
                    (*this)(i,j) = 0;
                }
            }
        }
    }


    template <typename T>
    template <typename Iter>
    Matrix<T>::Matrix(const size_t &rows, const size_t &columns, Iter containerBeginIt, Iter containerEndIt) : rows(rows), columns(columns) { 
        matrixData = new T[columns * rows];
        auto startOfFillIt = std::copy(containerBeginIt, containerEndIt, matrixData);
        std::fill(startOfFillIt, (matrixData+(rows*columns)), 0);
    }


    template <typename T>
    Matrix<T>::Matrix(const std::vector<std::vector<T>>& vec)   {
        rows = vec.size();
        columns = vec[0].size();
        matrixData = new T[rows * columns];
        for (int i=0; i<rows; i++)  {
            for (int j=0; j<columns; j++)  {
                (*this)(i,j) = vec[i][j];
            }
        }
    }

    
    template <typename T>
    Matrix<T>::Matrix(const Matrix<T> &other)   {
        this->rows = other.rows;
        this->columns = other.columns;
        matrixData = new T[other.rows * other.columns];
        for (int i=0; i<other.rows; i++)  {
            for (int j=0; j<other.columns; j++)  {
                (*this)(i,j) = other(i,j);
            }
        }
    }


    template <typename T>
    Matrix<T>::~Matrix()  {
        delete[] matrixData;
    }   

    
}