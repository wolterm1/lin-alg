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
    
    private:
    T* matrixData;
    size_t rows;
    size_t columns;
    void allocateForMatrixData();


    public:

    /*********************** Constructors **********************/

    template <typename Iter>
    Matrix(const size_t &rows, const size_t &colums, Iter begin, Iter end);

    Matrix(const std::vector<std::vector<T>>& vec);

    Matrix(const size_t &rows, const size_t &columns, const T& value);

    Matrix(const size_t &rows, const size_t &columns);

    Matrix(const Matrix<T> &other);

    static Matrix<T> createIdentity(const size_t& rows, const size_t& columns);

    Matrix<T>& operator=(Matrix<T>& other);

    ~Matrix();



    /*********************** Operators **********************/

    T& operator()(const size_t &rows, const size_t &colums) const;

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
   

    size_t getRows() const;
    size_t getColumns() const;

    
    

    /*********************** Iterator **********************/

    struct Iterator   {
        using iterator_concept = std::contiguous_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using difference_type  = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;


        Iterator(pointer p = nullptr) : ptr(p) {}
        
        pointer operator->() const { return ptr; }
        
        //inherited interface from std::bidirectional_iterator
        reference operator*() const { return *ptr; }

        Iterator& operator++()  { 
            ++ptr; 
            return *this;
        }

        Iterator operator++(int)  {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() { 
            --ptr; 
            return *this;
        }

        Iterator operator--(int) {
            auto tmp = *this;
            --(*this);
            return tmp;
        }

        Iterator& operator+=(difference_type n) { ptr += n; return *this; }
        Iterator operator+(difference_type n) const { return Iterator(ptr + n); } 
        friend Iterator operator+(difference_type n, const Iterator j)  { return n + j; }
        Iterator& operator-=(const difference_type n) { ptr -= n; return *this; }
        difference_type operator-(const Iterator j) const { return ptr - j.ptr; }
        Iterator operator-(const difference_type n) const { return Iterator(ptr - n); }
        reference operator[](difference_type n) const { return *(ptr + n); }
        auto operator<=>(const Iterator&) const = default;

        private:
        pointer ptr;
    };
  Iterator begin()  { return Iterator(matrixData); }
  Iterator end()  { return Iterator(matrixData + columns * rows); }

};

}

#include "matrix_operators.ipp"
#include "matrix_constructors.ipp"
