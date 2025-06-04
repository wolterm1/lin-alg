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
    explicit Vector(const size_t& p_size);
    explicit Vector(const std::vector<T>& vec);
    ~Vector();

    T& operator[](const size_t& pos) const;

    friend std::ostream& operator<<<T>(std::ostream& outputstream, const Vector<T>& vec);

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
T& Vector<T>::operator[](const size_t& pos) const {
    return vecData[pos];
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

}  // namespace linAlg
