#include <cmath>
#include <numeric>

#pragma once

namespace linAlg  {
    

    template <Numeric T>
    Matrix<T>::Matrix(const size_t &prows, const size_t &pcolumns, const T& value) : rows(prows) , columns(pcolumns) {
        allocateForMatrixData();
        for(int i=0; i<rows; i++)  {
            for(int j=0; j<columns;j++)  {
                (*this)(i,j) = value;
            }
        }
    }

    template <Numeric T>
    Matrix<T>::Matrix(const size_t &prows, const size_t &pcolumns) : rows(prows) , columns(pcolumns) {
        allocateForMatrixData();
    }


    template <Numeric T>
    template <typename Iter>
    Matrix<T>::Matrix(const size_t &prows, const size_t &pcolumns, Iter containerBeginIt, Iter containerEndIt) : rows(prows), columns(pcolumns) { 
        allocateForMatrixData();
        auto startOfFillIt = std::copy(containerBeginIt, containerEndIt, matrixData);
        std::fill(startOfFillIt, (matrixData+(rows*columns)), 0);
    }


    template <Numeric T>
    Matrix<T>::Matrix(const std::vector<std::vector<T>>& vec) : rows(vec.size()), columns (vec[0].size())  {
        allocateForMatrixData();
        for (int i=0; i<rows; i++)  {
            for (int j=0; j<columns; j++)  {
                (*this)(i,j) = vec[i][j];
            }
        }
    }

    template <Numeric T>
    Matrix<T> Matrix<T>::createIdentity(const size_t& rows, const size_t& columns) {
        Matrix<T> res(rows, columns);
        for (int i=0; i<res.rows; i++)  {
            for (int j=0; j<res.columns; j++)    {
                if (j == i) {
                    res(i,j) = 1;
                } else { 
                    res(i,j) = 0;
                }
            }
        }
        return res;
    }

    
    template <Numeric T>
    Matrix<T>::Matrix(const Matrix<T> &other) : rows(other.rows), columns(other.columns)    {
        allocateForMatrixData();
        for (int i=0; i<other.rows; i++)  {
            for (int j=0; j<other.columns; j++)  {
                (*this)(i,j) = other(i,j);
            }
        }
    }


    template <Numeric T>
    Matrix<T>::~Matrix()  {
        delete[] matrixData;
    }   

    template <Numeric T>
    void Matrix<T>::allocateForMatrixData()   {
        matrixData = new T[rows * columns];
    }
    
}