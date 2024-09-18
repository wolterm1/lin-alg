namespace linAlg  {
    

    template <typename T>
    Matrix<T>::Matrix(const size_t &rows, const size_t &columns)  {
        if(rows <= 0 || columns <= 0){
            throw std::invalid_argument("Unable to Create Matrix with Dimensions 0x0");
        }
        m_rows = rows;
        m_columns = columns;
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
    Matrix<T>::Matrix(const Matrix<T> &other) : m_columns(other.m_columns), m_rows(other.m_rows)  {
        m_ptr = new T[other.m_rows * other.m_columns];
        for (int i=0; i<other.m_rows; i++)  {
            for (int j=0; j<other.m_columns; j++)  {
                (*this)(i,j) = other(i,j);
            }
        }
    }


    template <typename T>
    Matrix<T>::~Matrix()  {
        delete[] m_ptr;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream &os, const Matrix<T> &mat)  {
        for(int i=0; i< mat.m_rows; i++)  {
            os << " | ";
            for (int j=0; j<mat.m_columns; j++)  {
                os << mat(i,j) << " | ";
            }
            os << "\n";
        }
        return os << "\n";
    }

    template <typename T>
    T& Matrix<T>::operator()(const size_t &row, const size_t &column) const {
        return *(m_ptr+column+(row*m_columns));
    }

    template <typename T>
    size_t Matrix<T>::getRows() const  {
        return m_rows;
    }

    template <typename T>
    size_t Matrix<T>::getColumns() const  {
        return m_columns;
    }

    template <typename T>
    bool Matrix<T>::operator==(const Matrix<T> &other) const  {
        if(m_rows != other.m_rows || m_columns != other.m_columns)  {
            return false;
        }
    }    
}


//should empty matrizes be constructed? operator== fails for size 0.