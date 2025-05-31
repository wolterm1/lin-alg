#include <iostream>
#include <vector>
#include <unordered_set>
#include "../include/matrix.hpp"




int main() {

    linAlg::Matrix<int> einheitsMatrix = linAlg::Matrix<int>::createIdentity(4,4);
    std::cout<< "einheitsMatrix: \n" << einheitsMatrix << std::endl;

    linAlg::Matrix<int> fillMatrix(4, 4, 3);
    std::cout<< "fillMatrix: \n" << fillMatrix << std::endl;

    std::unordered_multiset<long long> multiset({213,23,4,345});
    linAlg::Matrix<int> itMat(2, 4, multiset.begin(), multiset.end());
    std::cout<< "Constructed Matrix from begin and end iterators from multiset {213,23,4,345} \n" << itMat << std::endl;


    linAlg::Matrix<int> vecMat({{1,2,3},
                                {4,5,6},
                                {7,8,9}});
    std::cout << "vectorvectorMatrix: \n" <<vecMat << std::endl;

    linAlg::Matrix<int> xMat = linAlg::Matrix<int>::createIdentity(4,4);
    std::cout << "xMat: \n" <<xMat << std::endl;

    std::cout << "testing iterator, range based for-loop: " << std::endl;
    for (auto el : xMat) {
        std::cout << el;
    } std::cout << "\n" << std::endl;

    std::cout << "testing move assignment operator" << std::endl;
    linAlg::Matrix<int> tmpMat = linAlg::Matrix<int>::createIdentity(4,4);
    linAlg::Matrix<int> targetMat = std::move(tmpMat);
    std::cout << "moved Mat:" << tmpMat << "\n targetMat" << targetMat << std::endl;
}
