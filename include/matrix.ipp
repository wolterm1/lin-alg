#include <iostream>
#include <exception>

template <typename T> 
class Matrix {
    private:
    T* m_ptr;//point to start of arrs of pointers, this way memory for matrix can be allocated at runtime
    size_t m_rows;
    size_t m_columns;
    
    public:
    /// @brief Constructs identity matrix
    Matrix(const size_t &rows, const size_t &columns);
    /// @brief Copy-Constructor
    Matrix(const Matrix<T> &other); 
    /// @brief Move-Constructor 
    Matrix(Matrix<T>&& other) noexcept;
    
    /// @brief Destructor
    ~Matrix();
     
    Matrix<T>& operator=(Matrix<T> other);
    bool operator==(const Matrix<T> &other) const;
    bool operator!=(const Matrix<T> &other) const;
    T& operator()(const size_t &i, const size_t &j) const;
    
    Matrix<T> operator*(const T &skalar);
    Matrix<T> operator*(const Matrix<T> &other);
    Matrix<T> operator+(const Matrix<T> &other);

    
    size_t getRows() const;
    size_t getColumns() const;
    

    void Print();
    template <typename x>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<x> &Mat);

    friend void swap(Matrix<T> &first, Matrix<T> &second){
        using std::swap;
        swap(first.m_rows, second.m_rows);
        swap(first.m_columns, second.m_columns);
        swap(first.m_ptr, second.m_ptr);
    }
};








#include "matrix.ipp"
