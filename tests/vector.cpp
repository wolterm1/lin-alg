#include <vector>
#include "../include/vector.hpp"

using linAlg::Vector;

int main() {

    Vector<float> vecFl(std::vector<float>({1,2,3,4})) ;

    std::cout << vecFl;
    
}
