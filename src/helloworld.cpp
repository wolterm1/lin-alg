#include <iostream>
#include <vector>
#include <unordered_set>
#include "../include/matrix.hpp"




int main() {

    linAlg::Matrix<int> unitMatrix(4,4);
    std::cout<< "unitMatrix: \n" << unitMatrix << std::endl;


    linAlg::Matrix<int> fillMatrix(4,4, 3);
    std::cout<< "fillMatrix: \n" << fillMatrix << std::endl;


    std::unordered_multiset<long long> multiset({5132190783, 353264387356835, 12312364256248, 234125236724561, 123145125364263});
    linAlg::Matrix<int> itMat(2, 4, multiset.begin(), multiset.end());
    std::cout<< "ContainerIterableMatrix: \n" << itMat << std::endl;


    linAlg::Matrix<int> vecMat(std::vector<std::vector<int>>({{1,2,3},
                                                            {4,5,6},
                                                            {7,8,9}}));
    std::cout << "vectorvectorMatrix: \n" <<vecMat << std::endl;
     
}
