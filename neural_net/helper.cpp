#include "helper.hpp"
#include <cmath>
#include <random>
#include <fstream>

namespace nn {

using lin::Vector;

Vector<double> apply_activation_function(Vector<double> vec, const std::function<double(double)>& func) {
  for(size_t i = 0; i<vec.getSize(); ++i) {
    vec[i] = func(vec[i]);
  }
  return vec;
}

double sigmoid(double x) {
  return 1.0/(1.0+std::exp(-x));
}

double getRandom() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);
    return dist(gen);
}

std::vector<std::vector<uint8_t>> load_mnist_images(const std::string& filename){
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Datei nicht gefunden: " + filename);
    int32_t magic, num_images, rows, cols;
    file.read((char*)&magic, 4);
    file.read((char*)&num_images, 4);
    file.read((char*)&rows, 4);
    file.read((char*)&cols, 4);
    magic = __builtin_bswap32(magic);
    num_images = __builtin_bswap32(num_images);
    rows = __builtin_bswap32(rows);
    cols = __builtin_bswap32(cols);
    std::vector<std::vector<uint8_t>> images(num_images, std::vector<uint8_t>(rows * cols));
    for (int i = 0; i < num_images; ++i)
        file.read((char*)images[i].data(), rows * cols);
    return images;
}

std::vector<uint8_t> load_mnist_labels(const std::string& filename){
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Datei nicht gefunden: " + filename);

    int32_t magic, num_items;
    file.read((char*)&magic, 4);
    file.read((char*)&num_items, 4);

    magic = __builtin_bswap32(magic);
    num_items = __builtin_bswap32(num_items);

    std::vector<uint8_t> labels(num_items);
    file.read((char*)labels.data(), num_items);
    return labels;
}




void visualize_mnist_images(const std::vector<std::vector<uint8_t>>& vec) {
  for (size_t t=0; t < vec.size(); ++t) {
    std::cout << "Image " << t << ":\n";
    for (size_t k=0; k < vec[t].size(); ++k) {
      std::cout << (vec[t][k] > 140 ? '#' : ' ');
      if ((k+1) % 28 == 0) {
        std::cout << '\n';
      }
    }
    std::cout<< '\n';
  }
}

}
