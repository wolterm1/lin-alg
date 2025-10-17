#include "Optimizer.hpp"
#include <cmath>
#include "matrix.hpp"
#include "vector.hpp"
#include "linalg.hpp"

using lin::Vector;
using lin::Matrix;

namespace nn {

Optimizer::Optimizer(float lr, size_t batchSize) : learnRate(lr), batchSize(batchSize) {
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


  Vector<Matrix<float>> mean;
  Vector<Matrix<float>> variance;
  size_t timeStep;
  const float learnRate = 1e-3;
                            //
  const float beta1 = 0.9;
  const float beta2 = 0.999; 
  const float eps = 1e-8;
  // update step


  for (size_t i = 0; i < weights.getSize(); ++i) {
    wGradientSum[i] = wGradientSum[i] / batchSize;

    mean[i] = beta1 * mean[i] + (1-beta1) * wGradientSum[i];
    variance[i] = beta2 * variance[i] + (1.0F - beta2) * (wGradientSum[i] * wGradientSum[i]);

    auto meanCorrectedEst = mean[i] / (1.0F - std::pow(beta1, timeStep));
    auto varianceCorrectedEst = variance[i] / (1.0F - std::pow(beta2, timeStep));

    weights[i] -= learnRate * meanCorrectedEst / (std::sqrt(varianceCorrectedEst) + eps);





    biases[i] = biases[i] - learnRate * bGradientSum[i] / static_cast<float>(batchSize);
  }

}

}
