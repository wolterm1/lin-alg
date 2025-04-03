#include <iostream>
#include <exception>
#include <string>

namespace linAlg {

template <typename T>
class Matrix;

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T> &mat);




template <typename T> 
class Matrix {
    private:
    T* m_ptr;//point to start of arrs of pointers, this way memory for matrix can be allocated at runtime
    size_t rows;
    size_t columns;
    
    public:
    
    Matrix(const size_t &rows, const size_t &columns);
    Matrix(const Matrix<T> &other); 
    ~Matrix();

    
    template <typename x>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<x> &Mat);
    /// @brief Copy-Constructor
    
    T& operator()(const size_t &i, const size_t &j) const;
    size_t getRows() const;
    size_t getColumns() const;
    bool operator==(const Matrix<T> &other) const;
    /*
    /// @brief Move-Constructor 
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
};


}


#include "matrix.ipp"
