#include <matrix.hpp>
#include <vector.hpp>
#include <iostream>
#include <functional>

namespace nn {

class NeuralNet {
  public: 
  NeuralNet(size_t inputNodeCount, size_t outputNodeCount, size_t hiddenLayerCount, size_t hiddenNodeCount);
  explicit NeuralNet(const std::string& filename);
  void forward_pass();
  void train(size_t epochs, double learning_rate);
  double gradient_descent();
  void backpropagate();
  double calculate_error();

  void save_to_file(const std::string& filename);
  
  friend std::ostream& operator<<(std::ostream& outputstream, const NeuralNet& net);

  private:
  lin::Vector<lin::Matrix<double>> Weights;
  lin::Vector<lin::Vector<double>> Neurons; 
};

}
