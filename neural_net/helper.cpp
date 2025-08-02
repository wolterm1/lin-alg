#include "helper.hpp"
#include <cmath>

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

}
