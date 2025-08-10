#pragma once
#include "../include/vector.hpp"
#include <cstdint>
#include <functional>

namespace nn {

lin::Vector<float> apply_activation_function(lin::Vector<float> vec, const std::function<float(float)>& func);

float sigmoid(float x);

float getRandom();

lin::Vector<lin::Vector<uint8_t>> load_mnist_images(const std::string& filename);

lin::Vector<uint8_t> load_mnist_labels(const std::string& filename);

lin::Vector<lin::Vector<float>> normalize_images(const lin::Vector<lin::Vector<uint8_t>>& images);

lin::Vector<lin::Vector<float>> one_hot_encode(const lin::Vector<uint8_t>& labels);


void visualize_mnist_images(const lin::Vector<lin::Vector<uint8_t>>& vec);

void print_labels(const lin::Vector<uint8_t>& vec);

}
