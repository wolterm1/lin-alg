#include <cassert>
#include "../include/matrix.hpp"


int main() {

    using linAlg::Matrix;

    std::cout<< "testing operators" << '\n';
    Matrix<float> base(3,3,1.5);
    Matrix<float> compare_equal(3,3,1.5);
    Matrix<float> compare_unequal(3, 3, 2.0);
    std::cout<< "floatMatrix: \n" << base  << '\n';

    assert(base == compare_equal);
    assert(!(base == compare_unequal));

    assert(base != compare_unequal);
    assert(!(base != compare_equal));




    std::cout<< "\ndone" << '\n';


} 
