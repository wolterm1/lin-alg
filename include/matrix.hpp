#pragma once

#include <iostream>
#include <vector>

namespace linAlg {

//  template constraint
template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

template <Numeric T = int>

class Matrix {
   private:
    T *matrixData;
    size_t rows;
    size_t columns;
    void allocateForMatrixData();

   public:
    /*********************** Constructors **********************/

    template <typename Iter>
    Matrix(const size_t &rows, const size_t &pcolumns, Iter containerBeginIt, Iter containerEndIt);

    explicit Matrix(const std::vector<std::vector<T>> &vec);

    Matrix(const size_t &rows, const size_t &columns, const T &value);

    Matrix(const size_t &rows, const size_t &columns);

    Matrix(const Matrix<T> &other);

    Matrix(Matrix<T> &&other) noexcept;

    static auto createIdentity(const size_t &rows, const size_t &columns) -> Matrix<T>;

    ~Matrix();

    /*********************** Operators **********************/

    Matrix<T> &operator=(Matrix<T> other);

    Matrix<T> &operator=(Matrix<T> &&other) noexcept;

    T &operator()(const size_t &p_row, const size_t &column) const;

    bool operator==(const Matrix<T> &other) const;

    Matrix<T> operator+(const Matrix<T> &other);

    Matrix<T> &operator+=(const Matrix<T> &other);

    Matrix<T> operator*(const Matrix<T> &other);

    Matrix<T> operator*=(const Matrix<T> &other);

    size_t getRows() const;
    size_t getColumns() const;

    /*********************** helpers **********************/

    friend std::ostream &operator<<(std::ostream &outputstream, const Matrix<T> &mat) {
        for (int i = 0; i < mat.rows; ++i) {
            for (int j = 0; j < mat.columns; ++j) {
                outputstream << mat(i, j) << ", ";
            }
            outputstream << "\n";
        }
        return outputstream;
    }

    void swap(Matrix<T> &other) noexcept;

    /*********************** Iterator **********************/

    struct Iterator {
        using iterator_concept = std::contiguous_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        explicit Iterator(pointer p_ptr = nullptr) : ptr(p_ptr) {}

        pointer operator->() const { return ptr; }

        reference operator*() const { return *ptr; }

        Iterator &operator++() {
            ++ptr;
            return *this;
        }

        Iterator operator++(int) {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator &operator--() {
            --ptr;
            return *this;
        }

        Iterator operator--(int) {
            auto tmp = *this;
            --(*this);
            return tmp;
        }

        Iterator &operator+=(difference_type n) {
            ptr += n;
            return *this;
        }
        Iterator operator+(difference_type n) const { return Iterator(ptr + n); }
        friend Iterator operator+(difference_type n, const Iterator j) { return n + j; }
        Iterator &operator-=(const difference_type n) {
            ptr -= n;
            return *this;
        }
        difference_type operator-(const Iterator j) const { return ptr - j.ptr; }
        Iterator operator-(const difference_type n) const { return Iterator(ptr - n); }
        reference operator[](difference_type n) const { return *(ptr + n); }
        auto operator<=>(const Iterator &) const = default;

       private:
        pointer ptr;
    };
    Iterator begin() { return Iterator(matrixData); }
    Iterator end() { return Iterator(matrixData + (columns * rows)); }
};

}  // namespace linAlg

/**************************** Constructors
 * ****************************************/

namespace linAlg {

template <Numeric T>
Matrix<T>::Matrix(const size_t &prows, const size_t &pcolumns, const T &value)
    : rows(prows), columns(pcolumns) {
    allocateForMatrixData();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            (*this)(i, j) = value;
        }
    }
}

template <Numeric T>
Matrix<T>::Matrix(const size_t &prows, const size_t &pcolumns) : rows(prows), columns(pcolumns) {
    allocateForMatrixData();
}

template <Numeric T>
template <typename Iter>
Matrix<T>::Matrix(const size_t &prows, const size_t &pcolumns, Iter containerBeginIt,
                  Iter containerEndIt)
    : rows(prows), columns(pcolumns) {
    allocateForMatrixData();
    auto startOfFillIt = std::copy(containerBeginIt, containerEndIt, matrixData);
    std::fill(startOfFillIt, (matrixData + (rows * columns)), 0);
}

template <Numeric T>
Matrix<T>::Matrix(const std::vector<std::vector<T>> &vec)
    : rows(vec.size()), columns(vec[0].size()) {
    allocateForMatrixData();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            (*this)(i, j) = vec[i][j];
        }
    }
}

template <Numeric T>
Matrix<T> Matrix<T>::createIdentity(const size_t &rows, const size_t &columns) {
    Matrix<T> res(rows, columns);
    for (int i = 0; i < res.rows; i++) {
        for (int j = 0; j < res.columns; j++) {
            if (j == i) {
                res(i, j) = 1;
            } else {
                res(i, j) = 0;
            }
        }
    }
    return res;
}

template <Numeric T>
Matrix<T>::Matrix(const Matrix<T> &other) : rows(other.rows), columns(other.columns) {
    allocateForMatrixData();
    for (int i = 0; i < other.rows; i++) {
        for (int j = 0; j < other.columns; j++) {
            (*this)(i, j) = other(i, j);
        }
    }
}

template <Numeric T>
Matrix<T>::Matrix(Matrix<T> &&other) noexcept : rows(other.rows), columns(other.columns) {
    matrixData = other.matrixData;
    other.matrixData = nullptr;
    other.rows = 0;
    other.columns = 0;
}

template <Numeric T>
Matrix<T>::~Matrix() {
    delete[] matrixData;
}

template <Numeric T>
void Matrix<T>::allocateForMatrixData() {
    matrixData = new T[rows * columns];
}

}  // namespace linAlg

/**********************************Operators************************************************/

namespace linAlg {

template <Numeric T>
T &Matrix<T>::operator()(const size_t &p_row, const size_t &p_column) const {
    return *(matrixData + p_column + (p_row * columns));
}

template <Numeric T>
size_t Matrix<T>::getRows() const {
    return rows;
}

template <Numeric T>
size_t Matrix<T>::getColumns() const {
    return columns;
}

template <Numeric T>
bool Matrix<T>::operator==(const Matrix<T> &other) const {
    if (rows != other.rows || columns != other.columns) {
        return false;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if ((*this)(i, j) != other(i, j)) {
                return false;
            }
        }
    }
    return true;
}

template <Numeric T>
void Matrix<T>::swap(Matrix<T> &other) noexcept {
    std::swap(this->rows, other.rows);
    std::swap(this->columns, other.columns);
    std::swap(this->matrixData, other.matrixData);
}

template <Numeric T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> other) {
    // copy and swap idiom, param by value to avoid manually creating copy and avoid mutating *this
    // when creating copy fails
    swap(other);
    return *this;
}

template <Numeric T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&other) noexcept {
    matrixData = other.matrixData;
    rows = other.rows;
    columns = other.columns;
    other.matrixData = nullptr;
    other.rows = 0;
    other.columns = 0;
}
}  // namespace linAlg
