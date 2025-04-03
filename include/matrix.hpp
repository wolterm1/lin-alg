#include <iostream>
#include <exception>
#include <string>
#include <vector>

namespace linAlg {

//template declarations needed for friend operator<< overload function 
template <typename T>
class Matrix;

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T> &mat);


template <typename T> 
class Matrix {
    public:

    template <typename Iter>
    Matrix(const size_t &rows, const size_t &colums, Iter begin, Iter end);

    Matrix(const size_t &rows, const size_t &columns);

    Matrix(const Matrix<T> &other);
     
    ~Matrix();
    
    T& operator()(const size_t &rows, const size_t &colums) const;
    size_t getRows() const;
    size_t getColumns() const;
    bool operator==(const Matrix<T> &other) const;


    /*
    Matrix(Matrix<T>&& other) noexcept;

    //mach das hier wie beim ostream overload
    friend void swap(Matrix<T> &first, Matrix<T> &second){
        using std::swap;
        swap(first.m_rows, second.m_rows);
        swap(first.m_columns, second.m_columns);
        swap(first.m_ptr, second.m_ptr);
    }
    */
    friend std::ostream& operator<< <T> (std::ostream& os, const Matrix<T> &mat);


    private:
    T* m_ptr;
    size_t rows;
    size_t columns;
};

}

#include "matrix.ipp"
