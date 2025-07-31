#include <matrix.hpp>
#include <vector.hpp>

class NeuralNet {
  public: 
  NeuralNet(size_t inputNodeCount, size_t outputNodeCount, size_t hiddenLayerCount, size_t hiddenNodeCount);
  void forward_pass();
  private:
  lin::Vector<lin::Matrix<double>> Weights;
  lin::Vector<lin::Vector<double>> Neurons; 
};
