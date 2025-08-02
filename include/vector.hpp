#pragma once

#include <cstddef>
#include <iostream>

#include "concepts.hpp"

namespace lin {

template <TensorElement T>
class Vector;

template <TensorElement T>
std::ostream &operator<<(std::ostream &outputstream, const Vector<T> &vec);

template <TensorElement T>
bool checkEqualDimensions(const Vector<T> &first, const Vector<T> &second);

template <TensorElement T>
class Vector {
 public:
  // rule of five
  Vector(const Vector<T> &other);
  Vector(Vector<T> &&vec) noexcept;
  Vector<T> &operator=(const Vector<T> &other);
  Vector<T> &operator=(Vector<T> &&other) noexcept;
  Vector();
  ~Vector();

  explicit Vector(const size_t &p_size);
  Vector(const size_t &psize, const T& fillElement);
  Vector(const std::initializer_list<T> &init);

  bool operator==(const Vector<T> &other) const;
  T &operator[](const size_t &pos) const;
  Vector<T> &operator+=(const Vector<T> &other);
  Vector<T> operator+(const Vector<T> &other);
  Vector<T> &operator-=(const Vector<T> &other);
  Vector<T> operator-(const Vector<T> &other);
  Vector<T> &operator*=(const T &scalar);
  Vector<T> operator*(const T &scalar);

  friend std::ostream &operator<< <T>(std::ostream &outputstream, const Vector<T> &vec);

  void swap(Vector<T> &) noexcept;
  size_t getSize() const;

 private:
  T *vecData;
  size_t size;
  void allocateForVecData();
};



template <TensorElement T>
Vector<T>::Vector() : size(0) {
  allocateForVecData();
}
template <TensorElement T>
Vector<T>::Vector(const size_t &p_size) : size(p_size) {
  allocateForVecData();
}

template <TensorElement T>
Vector<T>::Vector(const size_t &psize, const T& fillElement) : size(psize) {
  allocateForVecData();
  for (size_t i=0; i<size; ++i) {
    (*this)[i] = fillElement;
  }
}

template <TensorElement T>
Vector<T>::Vector(const std::initializer_list<T> &init) : size(init.size()) {
  allocateForVecData();
  std::copy(init.begin(), init.end(), vecData);
}

template <TensorElement T>
Vector<T>::Vector(const Vector<T> &other) : size(other.size) {
  allocateForVecData();
  for (int i = 0; i < size; ++i) {
    (*this)[i] = other[i];
  }
}

template <TensorElement T>
Vector<T>::Vector(Vector<T> &&movedVec) noexcept : vecData(movedVec.vecData), size(movedVec.size) {
  movedVec.vecData = nullptr;
  movedVec.size = 0;
}

template <TensorElement T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
  if (this != &other) {
    Vector<T> copy(other);
    swap(copy);
  }
  return *this;
}

template <TensorElement T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  swap(other);
  return *this;
}

template <TensorElement T>
bool Vector<T>::operator==(const Vector<T> &other) const {
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

template <TensorElement T>
T &Vector<T>::operator[](const size_t &pos) const {
  return vecData[pos];
}

template <TensorElement T>
Vector<T> &Vector<T>::operator+=(const Vector<T> &other) {
  checkEqualDimensions(*this, other);
  for (int i = 0; i < size; ++i) {
    (*this)[i] += other[i];
  }
  return *this;
}

template <TensorElement T>
Vector<T> Vector<T>::operator+(const Vector<T> &other) {
  Vector<T> copy(*this);
  copy += other;
  return copy;
}

template <TensorElement T>
Vector<T> &Vector<T>::operator-=(const Vector<T> &other) {
  checkEqualDimensions(*this, other);
  for (int i = 0; i < size; ++i) {
    (*this)[i] -= other[i];
  }
  return *this;
}

template <TensorElement T>
Vector<T> Vector<T>::operator-(const Vector<T> &other) {
  Vector<T> copy(*this);
  copy -= other;
  return copy;
}

template <TensorElement T>
Vector<T> &Vector<T>::operator*=(const T &scalar) {
  for (int i = 0; i < size; ++i) {
    (*this)[i] *= scalar;
  }
  return *this;
}

template <TensorElement T>
Vector<T> Vector<T>::operator*(const T &scalar) {
  Vector<T> copy(*this);
  copy *= scalar;
  return copy;
}

template <TensorElement T>
Vector<T>::~Vector() {
  delete[] vecData;
}

template <TensorElement T>
void Vector<T>::allocateForVecData() {
  vecData = new T[size];
}

template <TensorElement T>
void Vector<T>::swap(Vector<T> &other) noexcept {
  std::swap(vecData, other.vecData);
  std::swap(size, other.size);
}

template <TensorElement T>
size_t Vector<T>::getSize() const {
  return size;
}

/***** friend functons *****/

template <TensorElement T>
bool checkEqualDimensions(const Vector<T> &first, const Vector<T> &second) {
  return first.getSize() == second.getSize();
}

template <TensorElement T>
std::ostream &operator<<(std::ostream &outputstream, const Vector<T> &vec) {
  for (int i = 0; i < vec.size -1; i++) {
    outputstream << vec[i] << ", ";
  }
  outputstream << vec[vec.size - 1] << '\n';
  return outputstream;
}

}  // namespace linAlg
