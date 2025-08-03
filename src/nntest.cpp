#include "../neural_net/net.hpp"
#include "helper.hpp"
#include <iostream>


int main() {
  nn::NeuralNet net(24, 9, 4, 4);
  std::cout << net << "\n";
  size_t epochs = 0;
  //std::cin >> epochs;
  //net.train(epochs,1.0);
  //std::cout << net << "\n";

  auto training_data = nn::load_mnist_images("data/train-images-idx3-ubyte");
     
  nn::visualize_mnist_images(training_data);
  
  auto labels = nn::load_mnist_labels("data/train-labels-idx1-ubyte");
}
