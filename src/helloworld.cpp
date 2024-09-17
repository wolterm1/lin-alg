#include <iostream>
#include <vector>
#include <matrix.hpp>
#include <cstdint>
#include <utility>

int main () {

    //#################### Constructor/Destructor #################

    Matrix<float> testArr(3,3);
    //std::cout << "Normal Constructor: 3x3 Identity Matrix:" << "\n";
    //testArr.Print();

    Matrix<float> copyArr = testArr; 
    //std::cout << "Copy Constructor: 3x3 Identity Matrix:" << "\n";
    //testArr.Print();
    

    //#################### operators #########################

    //std::cout << "\nChecking Equality between 2 identical:" << "\n";
    
    if (testArr == copyArr)  {
        //std::cout << "== operator working" << "\n";
    }

    copyArr(1,1) = 4; 
    //std::cout << "inserting \"4\" at index:" << "\n";
    //copyArr.Print();
    
    //std::cout << "Checking Inequality between 2:" << "\n";
    if (testArr != copyArr)  {
        //std::cout << "!= operator working" << "\n";
    }




    std::cout << "\nCopy Constructor: Copying Identity:";
    Matrix<float> copyconstr = testArr;
    copyconstr.Print();

    
    std::cout << "Copy-Assignment Operator = : ";
    copyconstr = copyArr;
    copyconstr.Print();

    std::cout << "Skalar Mult: 3,5*" ;
    Matrix<float> skalarMat = copyconstr*3.5;
    skalarMat.Print();

    std::cout << "Matrix Addition : ";
    Matrix<float> addMat = skalarMat+skalarMat;
    addMat.Print();
    
    std::cout << "Move-Constructor should get called: \n";
    Matrix<float> moveToThisMat = std::move(skalarMat);
    moveToThisMat.Print();
    skalarMat.Print();
    std::cout << sizeof(skalarMat);

    std::cout << "\n" << skalarMat << std::endl;
}
