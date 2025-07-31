#pragma once
#include "matrix.hpp"
#include "vector.hpp"

namespace lin {

template <Numeric T, TensorElement X>
void checkEqualMatrixColumnsToVectorSize(const Matrix<T> &mat, const Vector<X> &vec) {
  if (mat.getColumns() != vec.getSize()) {
    std::string msg =
        "Wrong dimensions for Matrix*Vector:\n MatrixColumns:" + std::to_string(mat.getColumns()) +
        "\nVector size:\n" + std::to_string(vec.getSize());
    throw std::invalid_argument(msg);
  }
}

template <Numeric T, TensorElement X>
void checkEqualVectorSize(const Vector<T> &first, const Vector<X> &second) {
  if (first.getSize() != 3 || second.getSize() != 3) {
    std::string msg = "Wrong dimensions for Crossproduct: " + std::to_string(first.getSize()) +
                      "x" + std::to_string(second.getSize());
    throw std::invalid_argument(msg);
  }
}

template <Numeric T>
Vector<T> cross(const Vector<T> &a, const Vector<T> &b) {
  return Vector<T>({(a[1] * b[2]) - (a[2] * b[1]),
                    (a[2] * b[0]) - (a[0] * b[2]),
                    (a[0] * b[1]) - (a[1] * b[0])});
}

template <Numeric T>
T dot(const Vector<T> &firstVec, const Vector<T> &secondVec) {
  checkEqualDimensions(firstVec, secondVec);
  T result = 0;
  for (int i = 0; i < firstVec.getSize(); ++i) {
    result += firstVec[i] * secondVec[i];
  }
  return result;
}

template <Numeric T>
Vector<T> operator*(const Matrix<T> &mat, const Vector<T> &vec) {
  // Matrix.rows has to be equal to vector length, resulting vector has matrix
  // row dimensions
  checkEqualMatrixColumnsToVectorSize(mat, vec);
  Vector<T> result(mat.getRows());
  for (int i = 0; i < mat.getRows(); ++i) {
    T tmp = 0;
    for (int j = 0; j < mat.getColumns(); ++j) {
      tmp += mat(i, j) * vec[j];
    }
    result[i] = tmp;
  }
  return result;
}

}  // namespace lin
