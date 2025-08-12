#include <matrix.hpp>
#include <vector.hpp>
#include <iostream>

namespace nn {

class NeuralNet {
  public: 
  NeuralNet(size_t inputNodeCount, size_t outputNodeCount, size_t hiddenLayerCount, size_t hiddenNodeCount);
  void train(const lin::Vector<lin::Vector<float>>& trainingData, const lin::Vector<lin::Vector<float>>& labels, size_t epochs, float learningRate);
  double gradient_descent();
  void forward_pass(const lin::Vector<float>& inputData);
  void backpropagation(const lin::Vector<float>& targetLabel, float learnRate);
  double calculate_error();

  void save_to_file(const std::string& filename);
  explicit NeuralNet(const std::string& filename);

  friend std::ostream& operator<<(std::ostream& outputstream, const NeuralNet& net);

  private:

  size_t inputNodeCount;
  size_t outputNodeCount;
  size_t hiddenLayerCount;
  size_t hiddenNodeCount;

  lin::Vector<lin::Vector<float>> zvalues; // pre activation function neuron values
  lin::Vector<lin::Vector<float>> neurons; 
  lin::Vector<lin::Matrix<float>> weights;
  lin::Vector<lin::Vector<float>> biases;
  
  // change this to apply function to set weights
  void init_net();
  void init_neurons();
  void init_zvalues();
  void init_weights();
  void init_biases();

};

}
