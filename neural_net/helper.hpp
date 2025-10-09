#pragma once
#include "../include/vector.hpp"
#include <cstdint>
#include <functional>
#include <utility>

namespace nn {

lin::Vector<float> apply_activation_function(lin::Vector<float>& vec, const std::function<float(float)>& func);

void shuffle(lin::Vector<lin::Vector<float>>& trainingData, lin::Vector<lin::Vector<float>>& labels);

int getIndexOfMax(lin::Vector<float>& vec);

float sigmoid(float x);

float sigmoid_derivative(float x);

lin::Vector<float> softmax(const lin::Vector<float>& inputVector);

float uniform_distribution_in(float lower, float upper);

float calculate_mse(const lin::Vector<float>& actual, const lin::Vector<float>& target);

lin::Vector<lin::Vector<uint8_t>> load_mnist_images(const std::string& filename);

lin::Vector<uint8_t> load_mnist_labels(const std::string& filename);

lin::Vector<lin::Vector<float>> normalize_images(const lin::Vector<lin::Vector<uint8_t>>& images);

lin::Vector<lin::Vector<float>> one_hot_encode(const lin::Vector<uint8_t>& labels);

void visualize_mnist_images(const lin::Vector<lin::Vector<uint8_t>>& vec);

void print_labels(const lin::Vector<uint8_t>& vec);

std::stringstream genTimeStampForFilename(const std::string& filename); 


}
