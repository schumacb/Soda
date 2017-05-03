#pragma once

#include "algorithm.hpp"

// forward declaration
namespace cv {
class Mat;
}

namespace soda {

namespace pluginapi {

class ImageProcessor : public AlgorithmNode {

protected:
  explicit ImageProcessor(QObject *parent = 0) : AlgorithmNode(parent) {}

public:
  virtual ~ImageProcessor() {}

public slots:
  void process(cv::Mat);
};

} // pluginapi

} // soda
