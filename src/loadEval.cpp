#include "../neural_net/net.hpp"
#include "helper.hpp"
#include "string"

int main() {
  std::string str;
  std::cin >> str;
  auto net = nn::NeuralNet::load_from_file(str);

  auto testData = nn::normalize_images(nn::load_mnist_images("data/t10k-images-idx3-ubyte"));
  auto testLabels = nn::one_hot_encode(nn::load_mnist_labels("data/t10k-labels-idx1-ubyte"));

  std::cout << net.evaluate(testData, testLabels);
}

