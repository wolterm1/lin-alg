#include <iostream>
#include <vector>
#include "../include/matrix.hpp"
#include <cstdint>
#include <utility>

int main () {

    //#################### Constructor/Destructor #################
    
    linAlg::Matrix<int> mat4(4,4);
    std::cout<< mat4 << std::endl;
}
