#pragma once 

namespace linAlg    {


    template <typename T>
        T& Matrix<T>::operator()(const size_t &row, const size_t &column) const {
            return *(matrixData+column+(row*columns));
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
                    os << mat(i,j) << ", ";
                }
                os << "\n";
            }
            return os;
        }

        
}
