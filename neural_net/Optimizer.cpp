#include "Optimizer.hpp"
#include <cmath>
#include "matrix.hpp"
#include "vector.hpp"
#include "linalg.hpp"

using lin::Vector;
using lin::Matrix;

namespace nn {

constexpr auto square_root = [](float x) { return std::sqrt(x); };


Optimizer::Optimizer(float lr) : learnRate(lr) {
}


void Optimizer::step(Vector<Matrix<float>>& weights, Vector<Vector<float>>& biases,
                      Vector<Matrix<float>>& wGradientSum, Vector<Vector<float>>& bGradientSum) {
  for (size_t i = 0; i < weights.getSize(); ++i) {

    wGradientSum[i] = Matrix(wGradientSum[i].getRows(), wGradientSum[i].getColumns(), 0.0F);
    bGradientSum[i] = Vector(bGradientSum[i].getSize(), 0.0F);
  }
  std::cout << "step called";
}


void Optimizer::computeAdam(Vector<Matrix<float>>& weights, Vector<Vector<float>>& biases,
                      Vector<Matrix<float>>& wGradientSum, Vector<Vector<float>>& bGradientSum) {

  Vector<Matrix<float>> weightMean;
  Vector<Matrix<float>> weightVariance;
  Vector<Vector<float>> biasMean;
  Vector<Vector<float>> biasVariance;
  size_t stepTime;
  const float learnRate = 1e-3;
                            //
  const float beta1 = 0.9;
  const float beta2 = 0.999; 
  const float eps = 1e-8;
  // update step


  for (size_t i = 0; i < weights.getSize(); ++i) {
    weightMean[i] = beta1 * weightMean[i] + (1-beta1) * wGradientSum[i];
    weightVariance[i] = beta2 * weightVariance[i] + (1.0F - beta2) * (wGradientSum[i].hadamardProductInplace(wGradientSum[i]));
    auto weightMeanCorrectedEst = weightMean[i] / (1.0F - std::pow(beta1, stepTime));
    auto weightVarianceCorrectedEst = weightVariance[i] / (1.0F - std::pow(beta2, stepTime));
    weights[i] -= learnRate * weightMeanCorrectedEst.hadamardDivisionInplace(weightVarianceCorrectedEst.applyElementWiseFunction(square_root) + eps);



    biasMean[i] = beta1 * biasMean[i] + (1-beta1) * bGradientSum[i];
    biasVariance[i] = beta2 * biasVariance[i] + (1.0F - beta2) * (bGradientSum[i].hadamardProductInplace(bGradientSum[i]));
    auto biasMeanCorrectedEst = biasMean[i] / (1.0F - std::pow(beta1, stepTime));
    auto biasVarianceCorrectedEst = biasVariance[i] / (1.0F - std::pow(beta2, stepTime));
    biases[i] -= learnRate * biasMeanCorrectedEst.hadamardDivisionInplace(biasVarianceCorrectedEst.applyElementWiseFunction(square_root) + eps);
  }

}

}
