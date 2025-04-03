#include <iostream>
#include <vector>
#include "../include/matrix.hpp"
#include <cstdint>
#include <utility>


int main() {

    linAlg::Matrix<int> mat4(4,4);
    std::cout<< mat4 << std::endl;

    std::vector<int> vec({1,2,3,4,5,6,7,8});

    mat4.printFromIter(vec.begin(), vec.end());
    linAlg::Matrix<int> itMat(2, 4, vec.begin(), vec.end());
    std::cout<< itMat << std::endl;
     
}
