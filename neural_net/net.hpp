#include <matrix.hpp>
#include <vector.hpp>
#include <iostream>

class NeuralNet {
  public: 
  NeuralNet(size_t inputNodeCount, size_t outputNodeCount, size_t hiddenLayerCount, size_t hiddenNodeCount);
  void forward_pass();
  friend std::ostream& operator<<(std::ostream& outputstream, const NeuralNet& net);

  private:
  lin::Vector<lin::Matrix<double>> Weights;
  lin::Vector<lin::Vector<double>> Neurons; 
};


