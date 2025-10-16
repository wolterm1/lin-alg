#include "Optimizer.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "linalg.hpp"

using lin::Vector;
using lin::Matrix;

namespace nn {

Optimizer::Optimizer(float lr) : learnRate(lr) {
}


void Optimizer::step(Vector<Matrix<float>>& weights, Vector<Vector<float>>& biases,
                      Vector<Matrix<float>>& wGradientSum, Vector<Vector<float>>& bGradientSum,
                      size_t batchSize) {
  for (size_t i = 0; i < weights.getSize(); ++i) {
    weights[i] -= learnRate * wGradientSum[i] / static_cast<float>(batchSize);
    biases[i] -= learnRate * bGradientSum[i] / static_cast<float>(batchSize);
    wGradientSum[i] = Matrix(wGradientSum[i].getRows(), wGradientSum[i].getColumns(), 0.0F);
    bGradientSum[i] = Vector(bGradientSum[i].getSize(), 0.0F);
  }
  std::cout << "step called";
}

}
