#include <cassert>

#include "../include/linalg.hpp"
#include "../include/matrix.hpp"
#include "../include/vector.hpp"
using lin::Matrix;
using lin::Vector;

namespace {
void testDot() {
  Vector<int> firstVec({1, 2, 3});
  Vector<int> secondVec({2, 4, 8});

  assert(dot(firstVec, secondVec) == 34);
}

void testCross() {
  Vector<int> firstVec({1, 2, 3});
  Vector<int> secondVec({2, 4, 8});

  Vector<int> crossVector = cross(firstVec, secondVec);
  Vector<int> expected({4, -2, 0});

  assert(crossVector == expected);
}

void testMatrixVectorMult() {
  Matrix<int> mat({
      {1, 2, 3},
      {4, 5, 6}
  });
  std::cout << mat;
  Vector<int> vec({1, 0, -1});

  Vector<int> result = mat * vec;
  Vector<int> expected({-2, -2});

  assert(result == expected);
}
}  // namespace

int main() {
  std::cout << "testing \n";
  testDot();
  testCross();
  testMatrixVectorMult();
}
