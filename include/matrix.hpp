#include <iostream>
#include <exception>
#include <string>
#include <vector>

namespace linAlg {

//template constraint 
template <typename T> 
concept Numeric = std::is_arithmetic_v<T>;


template<Numeric T=int>
class Matrix {
    public:

    template <typename Iter>
    Matrix(const size_t &rows, const size_t &colums, Iter begin, Iter end);

    Matrix(const std::vector<std::vector<T>>& vec);

    Matrix(const size_t &rows, const size_t &columns, const T& value);

    Matrix(const size_t &rows, const size_t &columns);

    Matrix(const Matrix<T> &other);

    static Matrix<T> createIdentity(const size_t& rows, const size_t& columns);

    Matrix<T>& operator=(Matrix<T>& other);


    ~Matrix();

    T& operator()(const size_t &rows, const size_t &colums) const;
    size_t getRows() const;
    size_t getColumns() const;
    bool operator==(const Matrix<T> &other) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat)    {
        for (int i=0; i<mat.rows; ++i)  {
            for (int j=0; j<mat.columns; ++j)   {
                os << mat(i,j) << ", ";
            }
            os << "\n";
        }
        return os;
    }




    class iterator  {
        public:
        T* ptr_;
        iterator(T* ptr) : ptr_(ptr) {}
        
        iterator& operator++() {
            ++ptr_;
            return *this;
        }
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const iterator& other) const { return this->ptr_ == other.ptr_; }
        bool operator!=(const iterator& other) const { return this->ptr_ != other.ptr_; }

       
        T& operator*() const { return *ptr_; }
    };



    iterator begin() {
        return iterator(matrixData);
    }
    iterator end() {
        return iterator(matrixData + (rows * columns));
    }




    private:
    T* matrixData;
    size_t rows;
    size_t columns;
    void allocateForMatrixData();
};

}

#include "matrix_operators.ipp"
#include "matrix_constructors.ipp"
