#include "net.hpp"
#include "../include/linalg.hpp"
#include "helper.hpp"
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using lin::Vector;
using lin::Matrix;
using lin::hadamard_product;

namespace nn {

// allocates Weights, Neurons and Weights for given nn dimensions, biases start with 0
NeuralNet::NeuralNet(size_t inputNodeCount, size_t outputNodeCount, size_t hiddenLayerCount, size_t hiddenNodeCount) : inputNodeCount(inputNodeCount), outputNodeCount(outputNodeCount), hiddenLayerCount(hiddenLayerCount), hiddenNodeCount(hiddenNodeCount) {
  init_net();
}

void NeuralNet::init_net() {
  init_neurons();
  init_zvalues();
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

void NeuralNet::init_zvalues() {
  zvalues = Vector<Vector<float>>(hiddenLayerCount+2);
  zvalues[0] = Vector<float>(inputNodeCount, 0.0f);
  for (size_t currentLayer = 1; currentLayer <= hiddenLayerCount; ++currentLayer) {
    zvalues[currentLayer] = Vector<float>(hiddenNodeCount, 0.0f);
  }
  zvalues[hiddenLayerCount+1] = Vector<float>(outputNodeCount, 0.0f);
}

// Xavier Weight Init
void NeuralNet::init_weights() {
  weights = Vector<Matrix<float>>(hiddenLayerCount+1);
  for (size_t i=0; i <= hiddenLayerCount; ++i) {
    size_t fan_in = neurons[i].getSize(); 
    size_t fan_out = neurons[i+1].getSize(); 
    float limit = std::sqrt(6.0f / (static_cast<float>(fan_in) + static_cast<float>(fan_out)));
    weights[i] = Matrix<float>(neurons[i+1].getSize(), neurons[i].getSize(), std::bind(uniform_distribution_in, -limit, limit));
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
    zvalues[i] = (weights[i-1] * neurons[i-1]) + biases[i-1];
    if (i == neurons.getSize() - 1) {
      neurons[i] = softmax(zvalues[i]);
    } else {
      neurons[i] = apply_activation_function(zvalues[i], sigmoid); 
    }
  }
}

void NeuralNet::backpropagation(const Vector<float>& targetLabel, float learnRate) {
  // Backpropagation algorithm, Computes Error Vector for each Neuron Layer, starting at the Last Layer and uses dynamic Programming to compute Error Vectors in [0 , L-2]
  size_t L = neurons.getSize();
  Vector<Vector<float>> deltas(L);

  // compute delta Error Vector at last layer
  deltas[L-1] = neurons[L-1] - targetLabel;

  for (size_t i = L-2;  i>0; --i) {
    deltas[i] = hadamard_product(
        weights[i].getTranspose() * deltas[i+1],
        apply_activation_function(zvalues[i], sigmoid_derivative)
        );
  }

  // now deltas[i] contains error Vector for every Layer in {1, ..., L-1}
  for (size_t i = 1; i < L; ++i) {
    Matrix<float> grad_w = lin::outer_product(deltas[i], neurons[i-1]);
    const Vector<float>& grad_b = deltas[i];

    weights[i-1] -= learnRate * grad_w;
    biases[i-1] -= learnRate * grad_b;
  }
}

//takes in normalized images and one-hot encoded labels in [0,9]
void NeuralNet::train(const Vector<Vector<float>>& trainingData, const Vector<Vector<float>>& labels, size_t epochs, float learningRate) {
  for (size_t currentEpoch = 1; currentEpoch <= epochs; ++currentEpoch) {
    for (size_t i = 0; i < trainingData.getSize(); ++i) {
      this->forward_pass(trainingData[i]);
      this->backpropagation(labels[i], learningRate);
    }
    std::cout << " Epoch: "<< currentEpoch << " done, Output Neurons of last Training: " << neurons[hiddenLayerCount+1] << '\n';
  }
}

Vector<float> NeuralNet::classify(const Vector<float>& inputData) {
  this->forward_pass(inputData);
  return neurons[hiddenLayerCount+1];
}

void NeuralNet::save_to_file(const std::string& filename){

  std::fstream file(filename + ".nn", std::ios::trunc | std::ios::out | std::ios::binary);
  
  std::string magic = "KNNET";
  file.write(magic.data(), magic.length() * sizeof(char));

  size_t weightMatricesCount = weights.getSize(); 
  file.write(reinterpret_cast<char*>(&weightMatricesCount), sizeof(weightMatricesCount));

  for (size_t i = 0; i < weightMatricesCount; ++i) {

    size_t rows = weights[i].getRows();
    size_t cols = weights[i].getColumns();
    file.write(reinterpret_cast<char*>(&rows), sizeof(rows));
    file.write(reinterpret_cast<char*>(&cols), sizeof(cols));
    file.write(reinterpret_cast<char*>(weights[i].data()), rows * cols * sizeof(float));

    size_t biasSize = biases[i].getSize();
    file.write(reinterpret_cast<char*>(&biasSize), sizeof(biasSize));
    file.write(reinterpret_cast<char*>(biases[i].data()), biasSize * sizeof(float));
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
