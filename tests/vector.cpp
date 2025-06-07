#include "../include/vector.hpp"

#include <cassert>
#include <vector>

using linAlg::Vector;

void testDot() {
    Vector<int> firstVec({1, 2, 3});
    Vector<int> secondVec({2, 4, 8});

    assert(dot(firstVec, secondVec) == 34);
}

int main() {
    Vector<int> firstVec({1, 2, 3});
    Vector<int> secondVec({2, 4, 8});

    Vector<int> mov(firstVec + secondVec);

    std::cout << mov;

    testDot();
}
