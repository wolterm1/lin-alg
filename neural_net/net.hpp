#include <matrix.hpp>
#include <vector.hpp>
#include <iostream>

namespace nn {

class NeuralNet {
  public: 
  NeuralNet(size_t inputNodeCount, size_t outputNodeCount, size_t hiddenLayerCount, size_t hiddenNodeCount);
  NeuralNet(const lin::Vector<lin::Matrix<float>>& inWeights, const lin::Vector<lin::Vector<float>>& inBiases); 
  void train(const lin::Vector<lin::Vector<float>>& trainingData, const lin::Vector<lin::Vector<float>>& labels, size_t epochs, size_t batchSize, float learningRate);
  void forward_pass(const lin::Vector<float>& inputData);
  void backpropagation(const lin::Vector<float>& targetLabel, float learnRate);
  void update_weights(float LearnRate, size_t batchSize);
  lin::Vector<float> classify(const lin::Vector<float>& inputData);

  void save_to_file(const std::string& filename);
  static NeuralNet load_from_file(const std::string& filename); // factory method to construct a Neural Net from File

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
  lin::Vector<lin::Matrix<float>> weightGradientSum;
  lin::Vector<lin::Vector<float>> biasGradientSum;

  void init_net();
  void init_neurons();
  void init_zvalues();
  void init_weights();
  void init_biases();
  void init_gradients();

};

}
