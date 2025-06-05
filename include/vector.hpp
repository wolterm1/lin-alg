#pragma once

#include <cstddef>
#include <iostream>
#include <vector>

#include "concepts.hpp"

namespace linAlg {

template <Numeric T>
class Vector;

template <Numeric T>
std::ostream& operator<<(std::ostream& outputstream, const Vector<T>& vec);

template <Numeric T = int>
class Vector {
   public:
    // rule of five
    Vector(const Vector<T>& other);
    Vector(Vector<T>&& vec) noexcept;
    Vector<T>& operator=(const Vector<T>& other);
    Vector<T>& operator=(Vector<T>&& other) noexcept;
    ~Vector();

    explicit Vector(const size_t& p_size);
    explicit Vector(const std::vector<T>& vec);

    bool operator==(const Vector<T>& other);
    T& operator[](const size_t& pos) const;
    Vector<T>& operator+=(const Vector<T>& other);
    Vector<T> operator+(const Vector<T>& other);
    Vector<T>& operator-=(const Vector<T>& other);
    Vector<T> operator-(const Vector<T>& other);
    Vector<T>& operator*=(const T& scalar);
    Vector<T> operator*(const T& scalar);

    friend std::ostream& operator<< <T>(std::ostream& outputstream, const Vector<T>& vec);
    void swap(Vector<T>&) noexcept;

   private:
    T* vecData;
    size_t size;
    void allocateForVecData();
};

template <Numeric T>
Vector<T>::Vector(const size_t& p_size) : size(p_size) {
    allocateForVecData();
}

template <Numeric T>
Vector<T>::Vector(const std::vector<T>& vec) : size(vec.size()) {
    allocateForVecData();
    for (int i = 0; i < size; ++i) {
        (*this)[i] = vec[i];
    }
}

template <Numeric T>
Vector<T>::Vector(const Vector<T>& other) : size(other.size) {
    allocateForVecData();
    for (int i = 0; i < size; ++i) {
        (*this)[i] = other[i];
    }
}

template <Numeric T>
Vector<T>::Vector(Vector<T>&& movedVec) noexcept : vecData(movedVec.vecData), size(movedVec.size) {
    movedVec.vecData = nullptr;
    movedVec.size = 0;
}

template <Numeric T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) {
        Vector<T> copy(other);
        swap(copy);
    }
    return *this;
}

template <Numeric T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    swap(other);
    return *this;
}

template <Numeric T>
bool Vector<T>::operator==(const Vector<T>& other) {
    if (size != other.size) {
        return false;
    }
    for (int i = 0; i < size; ++i) {
        if ((*this)[i] != other[i]) {
            return false;
        }
    }
    return true;
}

template <Numeric T>
T& Vector<T>::operator[](const size_t& pos) const {
    return vecData[pos];
}

template <Numeric T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
    for (int i = 0; i < size; ++i) {
        (*this)[i] += other[i];
    }
    return *this;
}

template <Numeric T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) {
    Vector<T> copy(*this);
    copy += other;
    return copy;
}

template <Numeric T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& other) {
    for (int i = 0; i < size; ++i) {
        (*this)[i] -= other[i];
    }
    return *this;
}

template <Numeric T>
Vector<T> Vector<T>::operator-(const Vector<T>& other) {
    Vector<T> copy(*this);
    copy -= other;
    return copy;
}

template <Numeric T>
Vector<T>& Vector<T>::operator*=(const T& scalar) {
    for (int i = 0; i < size; ++i) {
        (*this)[i] *= scalar;
    }
    return *this;
}

template <Numeric T>
Vector<T> Vector<T>::operator*(const T& scalar) {
    Vector<T> copy(*this);
    copy *= scalar;
    return copy;
}

template <Numeric T>
Vector<T>::~Vector() {
    delete[] vecData;
}

template <Numeric T>
void Vector<T>::allocateForVecData() {
    vecData = new T[size];
}

template <Numeric T>
std::ostream& operator<<(std::ostream& outputstream, const Vector<T>& vec) {
    for (int i = 0; i < vec.size; i++) {
        outputstream << vec[i] << ", ";
    }
    outputstream << '\n';
    return outputstream;
}

template <Numeric T>
void Vector<T>::swap(Vector<T>& other) noexcept {
    std::swap(vecData, other.vecData);
    std::swap(size, other.size);
}

}  // namespace linAlg
