#pragma once 

namespace linAlg    {


    template <Numeric T>
        T& Matrix<T>::operator()(const size_t &row, const size_t &column) const {
            return *(matrixData+column+(row*columns));
        }

        template <Numeric T>
        size_t Matrix<T>::getRows() const  {
            return rows;
        }

        template <Numeric T>
        size_t Matrix<T>::getColumns() const  {
            return columns;
        }

        template <Numeric T>
        bool Matrix<T>::operator==(const Matrix<T> &other) const  {
            if(rows != other.rows || columns != other.columns)  {
                return false;
            }
        }

        template <Numeric T> 
        Matrix<T>& Matrix<T>::operator=(Matrix<T>& other)    {
            this->rows = other.rows;
            this->columns = other.columns;
            std::copy(other.begin(), other.end(), matrixData);
            return *this;
        }
        
}
