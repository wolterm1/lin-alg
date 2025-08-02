#include "net.hpp"
#include "../include/linalg.hpp"
#include "helper.hpp"
#include <cstdlib>

using lin::Vector;
using lin::Matrix;

namespace nn {

NeuralNet::NeuralNet(size_t inputNodeCount, size_t outputNodeCount, size_t hiddenLayerCount, size_t hiddenNodeCount) 
  : Neurons(hiddenLayerCount+2), Weights(hiddenLayerCount+1) {

  //input Nodes + bias, same for Weight Matrices and neurons
  Neurons[0] = Vector<double>(inputNodeCount, getRandom);
  Neurons[hiddenLayerCount+1] = Vector<double>(outputNodeCount, getRandom);
  for (size_t i = 1; i <= hiddenLayerCount; ++i) {
    Neurons[i] = Vector<double>(hiddenNodeCount, getRandom);
  }
  
  Weights[0] = Matrix<double>(inputNodeCount, hiddenLayerCount, getRandom);
  Weights[hiddenLayerCount] = Matrix<double>(hiddenLayerCount, outputNodeCount, getRandom);
  for (size_t i = 1; i < hiddenLayerCount; ++i) {
    Weights[i] = Matrix<double>(hiddenLayerCount, hiddenLayerCount, getRandom) ;
  }
}



void NeuralNet::forward_pass() {
  for (size_t i=1; i<Neurons.getSize(); ++i) {
    //todo: append biases and activation function
    Neurons[i] = apply_activation_function(Neurons[i-1] * Weights[i-1], sigmoid); 
  }
}

void NeuralNet::train(size_t epochs, double learning_rate) {
  for(size_t i = 0; i<epochs; ++i) { 
    this->forward_pass();
  }
}



std::ostream& operator<<(std::ostream& outputstream, const NeuralNet& net){
  outputstream << "Weight Matrices: \n";
  for (size_t i = 0; i < net.Weights.getSize(); ++i) {
    outputstream << net.Weights[i] << '\n';
  }

  outputstream << "Neuron Vectors: \n";
  for (size_t i = 0; i < net.Neurons.getSize(); ++i) {
    outputstream << net.Neurons[i] << '\n';
  }

  return outputstream;
}

}
