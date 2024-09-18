#include <iostream>
#include <vector>
#include "matrix.hpp"
#include <cstdint>
#include <utility>

int main () {

    //#################### Constructor/Destructor #################
    
    linAlg::Matrix<float> testMat(3,3);
    std::cout << testMat;

    linAlg::Matrix<float> copiedTestMat = testMat;
    std::cout << copiedTestMat;
}
