#pragma once
#include "matrix.hpp"
#include "vector.hpp"

namespace nn {

class Optimizer {

  public:
  float learnRate;
  explicit Optimizer(float learnRate);
  void step(lin::Vector<lin::Matrix<float>>& weights, lin::Vector<lin::Vector<float>>& biases,
                      lin::Vector<lin::Matrix<float>>& wGradientSum, lin::Vector<lin::Vector<float>>& bGradientSum);
  void computeAdam();
};

}
