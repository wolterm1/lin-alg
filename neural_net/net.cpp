#include "net.hpp"
#include "../include/linalg.hpp"
#include "helper.hpp"
#include <cmath>
#include <cstdlib>

using lin::Vector;
using lin::Matrix;

namespace nn {

// allocates Weights, Neurons and Weights for given nn dimensions, biases start with 0
NeuralNet::NeuralNet(size_t inputNodeCount, size_t outputNodeCount, size_t hiddenLayerCount, size_t hiddenNodeCount) 
  : neurons(hiddenLayerCount+2), weights(hiddenLayerCount+1) , biases(hiddenLayerCount, 0.0){

  //input Nodes + bias, same for Weight Matrices and neurons
  neurons[0] = Vector<float>(inputNodeCount, 0);
  neurons[hiddenLayerCount+1] = Vector<float>(outputNodeCount, 0);
  for (size_t i = 1; i <= hiddenLayerCount; ++i) {
    neurons[i] = Vector<float>(hiddenNodeCount, 0);
  }
  
  weights[0] = Matrix<float>(inputNodeCount, hiddenLayerCount, getRandom);
  weights[hiddenLayerCount] = Matrix<float>(hiddenLayerCount, outputNodeCount, getRandom);
  for (size_t i = 1; i < hiddenLayerCount; ++i) {
    weights[i] = Matrix<float>(hiddenLayerCount, hiddenLayerCount, getRandom);
  }
}


void NeuralNet::init_weights() {
  for (size_t i=0; i<weights.getSize(); ++i) {
    float limit = std::sqrt(6.0f / (static_cast<float>(weights[i].getRows()) + static_cast<float>(weights[i].getColumns())));
    for (size_t r=0; r<weights[i].getRows(); ++r) {
      for (size_t c=0; c<weights[i].getColumns(); ++c) {
        weights[i](r,c) = 0.0;
      }
    }
  }
}

// initializes input Neurons with given inputVector and then computes neuron values with biases and activation Function
void NeuralNet::forward_pass(const Vector<float>& inputData) {
  neurons[0] = inputData;
  for (size_t i=1; i<neurons.getSize(); ++i) {
    neurons[i] = apply_activation_function((neurons[i-1] * weights[i-1]) + biases[i], sigmoid); 
  }
}

void NeuralNet::backward_pass(const Vector<float>& oneHotLabels) {

}
//takes in normalized images and one-hot encoded labels in [0,9]
void NeuralNet::train(const Vector<Vector<float>>& trainingData, const Vector<Vector<float>>& labels, size_t epochs, float learningRate) {
  for (size_t i = 0; i < trainingData.getSize(); ++i) {
    for (size_t currentEpoch; currentEpoch <= epochs; ++currentEpoch) {
      this->forward_pass(trainingData[i]);
      this->backward_pass(labels[i]);
    }
  }
}


std::ostream& operator<<(std::ostream& outputstream, const NeuralNet& net){
  outputstream << "Weight Matrices: \n";
  for (size_t i = 0; i < net.weights.getSize(); ++i) {
    outputstream << net.weights[i] << '\n';
  }

  outputstream << "Neuron Vectors: \n";
  for (size_t i = 0; i < net.neurons.getSize(); ++i) {
    outputstream << net.neurons[i] << '\n';
  }

  return outputstream;
}

}
