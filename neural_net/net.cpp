#include "net.hpp"

using lin::Vector;
using lin::Matrix;

NeuralNet::NeuralNet(size_t inputNodeCount, size_t outputNodeCount, size_t hiddenLayerCount, size_t hiddenNodeCount) 
  : Neurons(hiddenLayerCount+2), Weights(hiddenLayerCount+1) {

  Neurons[0] = Vector<double>(inputNodeCount);
  Neurons[hiddenLayerCount+1] = Vector<double>(outputNodeCount);
  for (size_t i = 1; i <= hiddenLayerCount; ++i) {
    Neurons[i] = Vector<double>(hiddenNodeCount);
  }
}

