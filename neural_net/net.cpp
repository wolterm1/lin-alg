#include "net.hpp"
#include "../include/linalg.hpp"

using lin::Vector;
using lin::Matrix;

NeuralNet::NeuralNet(size_t inputNodeCount, size_t outputNodeCount, size_t hiddenLayerCount, size_t hiddenNodeCount) 
  : Neurons(hiddenLayerCount+2), Weights(hiddenLayerCount+1) {

  Neurons[0] = Vector<double>(inputNodeCount, 10);
  Neurons[hiddenLayerCount+1] = Vector<double>(outputNodeCount,20);
  for (size_t i = 1; i <= hiddenLayerCount; ++i) {
    Neurons[i] = Vector<double>(hiddenNodeCount, 0);
  }
  
  Weights[0] = Matrix<double>(inputNodeCount, hiddenLayerCount, 1);
  Weights[hiddenLayerCount] = Matrix<double>(hiddenLayerCount, outputNodeCount, 9);
  for (size_t i = 1; i < hiddenLayerCount; ++i) {
    Weights[i] = Matrix<double>(hiddenLayerCount, hiddenLayerCount, 7);
  }
}


void NeuralNet::forward_pass() {
  for (size_t i=1; i<Neurons.getSize(); ++i) {
    Neurons[i] = Neurons[i-1] * Weights[i-1]; 
  }
}





std::ostream& operator<<(std::ostream& outputstream, const NeuralNet& net){
  outputstream << "Weights: \n";
  for (size_t i = 0; i < net.Weights.getSize(); ++i) {
    outputstream << net.Weights[i] << '\n';
  }

  outputstream << "Neurons: \n";
  for (size_t i = 0; i < net.Neurons.getSize(); ++i) {
    outputstream << net.Neurons[i] << '\n';
  }

  return outputstream;
}
