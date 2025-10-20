#pragma once
#include <iostream>
#include <vector.hpp>

namespace nn {
  using lin::Vector;

class ConfusionMatrix {
  public:
  explicit ConfusionMatrix(size_t classCount);
  void calculate(const Vector<int>& predictions, const Vector<int>& truth);

  private:
  size_t classCount;
  Vector<size_t> truePositives;
  Vector<size_t> trueNegatives;
  Vector<size_t> falsePositives;
  Vector<size_t> falseNegatives;

  void calculateTrueNegatives(size_t sampleCount);

  friend std::ostream& operator<<(std::ostream& os, const ConfusionMatrix& mat);
};

}
