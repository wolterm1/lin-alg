#pragma once
#include "../include/vector.hpp"
#include <cstdint>
#include <functional>

namespace nn {

lin::Vector<double> apply_activation_function(lin::Vector<double> vec, const std::function<double(double)>& func);

double sigmoid(double x);

double getRandom();

std::vector<std::vector<uint8_t>> load_mnist_images(const std::string& filename);

std::vector<uint8_t> load_mnist_labels(const std::string& filename);

void visualize_mnist_images(const std::vector<std::vector<uint8_t>>& vec);


}
