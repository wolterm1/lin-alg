#include "../include/vector.hpp"

#include <cassert>
#include <vector>

using linAlg::Vector;

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

int main() {
    testDot();
    testCross();

    Vector<int> firstVec({1, 2, 3});
    Vector<int> secondVec({2, 4, 8});
    Vector<int> mov(firstVec + secondVec);
    std::cout << mov;

    Vector<int> result = cross(Vector<int>({1, 2, 3}), Vector<int>{2, 4, 8});
    std::cout << result;
    
}
