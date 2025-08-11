#include "net.hpp"
#include "../include/linalg.hpp"
#include "helper.hpp"
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <random>

using lin::Vector;
using lin::Matrix;

namespace nn {

// allocates Weights, Neurons and Weights for given nn dimensions, biases start with 0
NeuralNet::NeuralNet(size_t inputNodeCount, size_t outputNodeCount, size_t hiddenLayerCount, size_t hiddenNodeCount) : inputNodeCount(inputNodeCount), outputNodeCount(outputNodeCount), hiddenLayerCount(hiddenLayerCount), hiddenNodeCount(hiddenNodeCount) {
  init_net();
}

void NeuralNet::init_net() {
  init_neurons();
  init_weights();
  init_biases();
}


void NeuralNet::init_neurons() {
  neurons = Vector<Vector<float>>(hiddenLayerCount+2);
  neurons[0] = Vector<float>(inputNodeCount, 0.0f);
  for (size_t currentLayer = 1; currentLayer <= hiddenLayerCount; ++currentLayer) {
    neurons[currentLayer] = Vector<float>(hiddenNodeCount, 0.0f);
  }
  neurons[hiddenLayerCount+1] = Vector<float>(outputNodeCount, 0.0f);
}

// Xavier Weight Init
void NeuralNet::init_weights() {
  weights = Vector<Matrix<float>>(hiddenLayerCount+1);
  for (size_t i=0; i <= hiddenLayerCount; ++i) {
    size_t fan_in = neurons[i].getSize(); 
    size_t fan_out = neurons[i+1].getSize(); 
    float limit = std::sqrt(6.0f / (static_cast<float>(fan_in) + static_cast<float>(fan_out)));
    weights[i] = Matrix<float>(neurons[i].getSize(), neurons[i+1].getSize(), std::bind(uniform_distribution_in, -limit, limit));
  }
}

void NeuralNet::init_biases() {
  biases = Vector<Vector<float>>(hiddenLayerCount+1);
  for (size_t currentLayer = 0; currentLayer <= hiddenLayerCount; ++currentLayer) {
    biases[currentLayer] = Vector<float>(neurons[currentLayer+1].getSize(), 0.01);
  }
}

// initializes input Neurons with given inputVector and then computes neuron values with biases and activation Function
void NeuralNet::forward_pass(const Vector<float>& inputData) {
  neurons[0] = inputData;
  for (size_t i=1; i<neurons.getSize(); ++i) {
    neurons[i] = apply_activation_function((neurons[i-1] * weights[i-1]) + biases[i-1], sigmoid); 
  }
}

void NeuralNet::backward_pass(const Vector<float>& oneHotLabel) {
  //calculateError(neurons[neurons.getSize()-1], oneHotLabel);
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
    outputstream << std::setprecision(2) << net.weights[i] << '\n';
  }

  outputstream << "\nBiases: \n";
  for (size_t i = 0; i < net.biases.getSize(); ++i) {
    outputstream << i << " : " << std::setprecision(2) <<  net.biases[i] << '\n';
  }


  outputstream << "\nNeuron Vectors: \n";
  for (size_t i = 0; i < net.neurons.getSize(); ++i) {
    outputstream << i << " : " << std::setprecision(2) <<  net.neurons[i] << '\n';
  }

  return outputstream;
}

}
