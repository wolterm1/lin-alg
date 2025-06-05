#include <vector>
#include "../include/vector.hpp"

using linAlg::Vector;

int main() {

    Vector<float> vecFl(std::vector<float>({1,2,3,4})) ;

    std::cout << vecFl;


    std::cout << "move constructing new vector with:" <<  vecFl;
    Vector<float> movedRes = std::move(vecFl);
    std::cout << "Move Constructr result: " << movedRes << "moved from vecFl:" <<  vecFl;
    
}
