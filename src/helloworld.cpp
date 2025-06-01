#include <iostream>
#include <vector>
#include <unordered_set>
#include "../include/matrix.hpp"




int main() {

    linAlg::Matrix<int> einheitsMatrix = linAlg::Matrix<int>::createIdentity(4,4);
    std::cout<< "einheitsMatrix: \n" << einheitsMatrix << '\n';

    linAlg::Matrix<int> fillMatrix(4, 4, 3);
    std::cout<< "fillMatrix: \n" << fillMatrix << '\n';

    std::unordered_multiset<long long> multiset({213,23,4,345});
    linAlg::Matrix<int> itMat(2, 4, multiset.begin(), multiset.end());
    std::cout<< "Constructed Matrix from begin and end iterators from multiset {213,23,4,345} \n" << itMat << '\n';


    linAlg::Matrix<int> vecMat({{1,2,3},
                                {4,5,6},
                                {7,8,9}});
    std::cout << "vecMatrix: \n" <<vecMat << '\n';

    linAlg::Matrix<int> Identity = linAlg::Matrix<int>::createIdentity(4,4);
    std::cout << "Identity: \n" <<Identity << '\n';


    std::cout << "swapping vecMatrix and Identity" << '\n';
    Identity.swap(vecMat);
    std::cout << "vecMat:\n "<< vecMat << "\n Identity: \n" << Identity << '\n';

    
    std::cout << "testing iterator, range based for-loop: " << '\n';
    for (auto matrixEntry : Identity) {
        std::cout << matrixEntry;
    } std::cout << "\n" << '\n';

    std::cout << "testing move assignment operator" << '\n';
    linAlg::Matrix<int> tmpMat = linAlg::Matrix<int>::createIdentity(4,4);
    linAlg::Matrix<int> targetMat = std::move(tmpMat);
    std::cout << "Moving tmpMat to target mat: \n tmpMat:" << tmpMat << "\n targetMat\n" << targetMat << '\n';
}
