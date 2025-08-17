#include "../neural_net/net.hpp"
#include "helper.hpp"
#include <iomanip>
#include <iostream>

using lin::Vector;

int main() {

  auto trainingData = nn::load_mnist_images("data/train-images-idx3-ubyte");
  auto trainingNormalizedImages = nn::normalize_images(trainingData);

  lin::Vector<uint8_t> trainingLabels = nn::load_mnist_labels("data/train-labels-idx1-ubyte");
  auto trainingOneHotLabels = nn::one_hot_encode(trainingLabels);

  nn::NeuralNet net(784, 10, 2, 128);
  net.train(trainingNormalizedImages, trainingOneHotLabels, 20, 0.01);



  auto testData = nn::load_mnist_images("data/t10k-images-idx3-ubyte");
  auto normalizedTestImages = nn::normalize_images(testData);

  lin::Vector<uint8_t> testLabels = nn::load_mnist_labels("data/train-labels-idx1-ubyte");
  auto testOneHotLabels = nn::one_hot_encode(testLabels);

  for(int i = 0; i < 10; ++i) {
    Vector<float> result = net.classify(normalizedTestImages[i]);
    std::cout << "Image " << i << " classified as: " << result << "\n";
  }

}
