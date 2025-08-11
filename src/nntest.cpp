#include "../neural_net/net.hpp"
#include "helper.hpp"
#include <iomanip>
#include <iostream>


int main() {




  auto trainingData = nn::load_mnist_images("data/train-images-idx3-ubyte");
  //nn::visualize_mnist_images(training_data);
  auto normalizedImages = nn::normalize_images(trainingData);

  lin::Vector<uint8_t> labels = nn::load_mnist_labels("data/train-labels-idx1-ubyte");
  auto oneHotLabels = nn::one_hot_encode(labels);
  for (int i = 0; i < 10; ++i) {
    std::cout << "Label: " << static_cast<int>(labels[i]) << " : [" << oneHotLabels[i] << "]\n";
  }
  //nn::print_labels(labels);
  
  nn::NeuralNet net(784, 10, 4, 4);
  std::cout << "\n initial Net: " << net << "\n";

  net.forward_pass(normalizedImages[0]);
  std::cout << "\n Net After One forward_pass() : " << net << "\n";

  
  //net.train(normalizedImages, oneHotLabels, 1,1.0);
  //std::cout << net << "\n";
}
