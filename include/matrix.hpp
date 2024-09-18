#include <iostream>
#include <exception>
#include <string>

namespace linAlg {


template <typename T> 
class Matrix {
    private:
    T* m_ptr;//point to start of arrs of pointers, this way memory for matrix can be allocated at runtime
    size_t m_rows;
    size_t m_columns;
    
    public:
    /// @brief Constructs identity matrix
    Matrix(const size_t &rows, const size_t &columns);
    /// @brief Destructor
    ~Matrix();

    //since this is a friend function, devlare its own template,
    //in implementation we just use T
    template <typename x>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<x> &Mat);
    /// @brief Copy-Constructor
    Matrix(const Matrix<T> &other); 
    
    T& operator()(const size_t &i, const size_t &j) const;
    size_t getRows() const;
    size_t getColumns() const;
    bool operator==(const Matrix<T> &other) const;
    /*
    /// @brief Move-Constructor 
    Matrix(Matrix<T>&& other) noexcept;
    
     
    Matrix<T>& operator=(Matrix<T> other);
    bool operator!=(const Matrix<T> &other) const;
    
    Matrix<T> operator*(const T &skalar);
    Matrix<T> operator*(const Matrix<T> &other);
    Matrix<T> operator+(const Matrix<T> &other);

    
    

    void Print();


    //mach das hier wie beim ostream overload
    friend void swap(Matrix<T> &first, Matrix<T> &second){
        using std::swap;
        swap(first.m_rows, second.m_rows);
        swap(first.m_columns, second.m_columns);
        swap(first.m_ptr, second.m_ptr);
    }
    */
};

}






#include "matrix.ipp"
