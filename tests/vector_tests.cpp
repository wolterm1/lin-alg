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
  Vector<int> vec({1, 0, -1});

  Vector<int> result = mat * vec;
  Vector<int> expected({-2, -2});

  assert(result == expected);
}

void testCompMult() {
  Vector<int> vec({1, 2, -3});
  Vector<int> vec2({3,2,2});
  Vector<int> result = vec.hadamard_product(vec2);
  Vector<int> expected({3,4,-6});

  assert(result == expected);
}

void testVectorMatrixMult() {
  Vector<int> vec({2, 1, 1});
  Matrix<int> mat({
      {2,3},
      {1,4},
      {0,1}
  });
  Vector<int> result = vec * mat;
  Vector<int> expected({5,11});

  std::cout << vec << "* \n" << mat << ": \n";

  std::cout << result << '\n';
  assert(result == expected);
}
}  // namespace

int main() {
  std::cout << "testing \n";
  testDot();
  testCross();
  testMatrixVectorMult();
  testVectorMatrixMult();


  lin::Vector<int> vec({1,2,34,0,543,5,43});
  for (auto& el : vec) {
    std::cout << el;
  }
}
