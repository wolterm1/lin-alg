#pragma once


namespace linAlg  {
    

    template <typename T>
    Matrix<T>::Matrix(const size_t &rows, const size_t &columns)  {
        if(rows <= 0 || columns <= 0){
            throw std::invalid_argument("Unable to Create Matrix with Dimensions 0x0");
        }
        this->rows = rows;
        this->columns = columns;
        m_ptr = new T[rows*columns];
        for(int i=0; i<rows; i++)  {
            for(int j=0; j<columns;j++)  {
                if(i==j)  {
                    (*this)(i,j) = 1;
                } else {
                    (*this)(i,j) = 0;
                }
            }
        }
    }

    template <typename T>
    Matrix<T>::Matrix(const Matrix<T> &other) : columns(other.columns), rows(other.rows)  {
        m_ptr = new T[other.rows * other.columns];
        for (int i=0; i<other.rows; i++)  {
            for (int j=0; j<other.columns; j++)  {
                (*this)(i,j) = other(i,j);
            }
        }
    }


    template <typename T>
    Matrix<T>::~Matrix()  {
        delete[] m_ptr;
    }

    
    template <typename T>
    T& Matrix<T>::operator()(const size_t &row, const size_t &column) const {
        return *(m_ptr+column+(row*columns));
    }

    template <typename T>
    size_t Matrix<T>::getRows() const  {
        return rows;
    }

    template <typename T>
    size_t Matrix<T>::getColumns() const  {
        return columns;
    }

    template <typename T>
    bool Matrix<T>::operator==(const Matrix<T> &other) const  {
        if(rows != other.rows || columns != other.columns)  {
            return false;
        }
    }
    
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat)    {
        for (int i=0; i<mat.rows; ++i)  {
            for (int j=0; j<mat.columns; ++j)   {
                os << mat(i,j);
            }
            os << "\n";
        }
        return os;
    }

    
    
}


//should empty matrizes be constructed? operator== fails for size 0.