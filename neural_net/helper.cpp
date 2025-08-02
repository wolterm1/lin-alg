#include "helper.hpp"
#include <cmath>
#include <random>

namespace nn {

using lin::Vector;

Vector<double> apply_activation_function(Vector<double> vec, const std::function<double(double)>& func) {
  for(size_t i = 0; i<vec.getSize(); ++i) {
    vec[i] = func(vec[i]);
  }
  return vec;
}

double sigmoid(double x) {
  return 1.0/(1.0+std::exp(-x));
}

double getRandom() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);
    return dist(gen);
}

}
