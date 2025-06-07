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

template <Numeric T>
T dot(const Vector<T>& firstVec, const Vector<T>& secondVec);

template <Numeric T>
Vector<T> cross(const Vector<T>& a, const Vector<T>& b);

template <Numeric T>
bool checkEqualDimensions(const Vector<T>& first, const Vector<T>& second);

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
    Vector(const std::initializer_list<T>& init);

    bool operator==(const Vector<T>& other) const;
    T& operator[](const size_t& pos) const;
    Vector<T>& operator+=(const Vector<T>& other);
    Vector<T> operator+(const Vector<T>& other);
    Vector<T>& operator-=(const Vector<T>& other);
    Vector<T> operator-(const Vector<T>& other);
    Vector<T>& operator*=(const T& scalar);
    Vector<T> operator*(const T& scalar);

    friend std::ostream& operator<< <T>(std::ostream& outputstream, const Vector<T>& vec);

    void swap(Vector<T>&) noexcept;
    size_t getSize() const;

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
Vector<T>::Vector(const std::initializer_list<T>& init) : size(init.size()) {
    allocateForVecData();
    std::copy(init.begin(), init.end(), vecData);
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
bool Vector<T>::operator==(const Vector<T>& other) const {
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
void Vector<T>::swap(Vector<T>& other) noexcept {
    std::swap(vecData, other.vecData);
    std::swap(size, other.size);
}

template <Numeric T>
size_t Vector<T>::getSize() const {
    return size;
}

/***** friend functons *****/

template <Numeric T>
bool checkEqualDimensions(const Vector<T>& first, const Vector<T>& second) {
    return first.getSize() == second.getSize();
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
T dot(const Vector<T>& firstVec, const Vector<T>& secondVec) {
    checkEqualDimensions(firstVec, secondVec);
    T result = 0;
    for (int i = 0; i < firstVec.getSize(); ++i) {
        result += firstVec[i] * secondVec[i];
    }

    return result;
}

template <Numeric T>
Vector<T> cross(const Vector<T>& a, const Vector<T>& b) {
    if (a.getSize() != 3 || b.getSize() != 3) {
        std::string msg = "Wrong dimensions for Crossproduct: " + std::to_string(a.getSize()) +
                          "x" + std::to_string(b.getSize());
        throw std::invalid_argument(msg);
    }
    return Vector<T>({(a[1] * b[2]) - (a[2] * b[1]), (a[2] * b[0]) - (a[0] * b[2]),
                      (a[0] * b[1]) - (a[1] * b[0])});
}

}  // namespace linAlg
