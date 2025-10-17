#pragma once
#include "matrix.hpp"
#include "vector.hpp"

namespace nn {

class Optimizer {

  size_t batchSize; // move this outside optimizer
  public:
  float learnRate;



  
  double previosVt = 0;



  explicit Optimizer(float learnRate, size_t batchSize);
  void step(lin::Vector<lin::Matrix<float>>& weights, lin::Vector<lin::Vector<float>>& biases,
                      lin::Vector<lin::Matrix<float>>& wGradientSum, lin::Vector<lin::Vector<float>>& bGradientSum);
  void computeAdam();
};

}
