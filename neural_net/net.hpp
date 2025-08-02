#include <matrix.hpp>
#include <vector.hpp>
#include <iostream>
#include <functional>

namespace nn {

class NeuralNet {
  public: 
  NeuralNet(size_t inputNodeCount, size_t outputNodeCount, size_t hiddenLayerCount, size_t hiddenNodeCount);
  void forward_pass();
  void train(size_t epochs, double learning_rate);
  double gradient_descent();
  void backpropagate();
  double calculate_error();
  
  friend std::ostream& operator<<(std::ostream& outputstream, const NeuralNet& net);

  private:
  lin::Vector<lin::Matrix<double>> Weights;
  lin::Vector<lin::Vector<double>> Neurons; 
};

}
