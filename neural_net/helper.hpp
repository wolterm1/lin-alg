#pragma once
#include "../include/vector.hpp"
#include <functional>

namespace nn {

lin::Vector<double> apply_activation_function(lin::Vector<double> vec, const std::function<double(double)>& func);

double sigmoid(double x);

double getRandom();

}
