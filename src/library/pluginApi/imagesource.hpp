#pragma once

#include "algorithm.hpp"

// Forward declaration
namespace cv {
class Mat;
}

namespace soda {

namespace pluginapi {

class ImageSource : public AlgorithmNode {

protected:
  explicit ImageSource(QObject *parent = 0) : AlgorithmNode(parent) {}

public:
  virtual ~ImageSource() {}

signals:
  void imageReady(cv::Mat){};
};

} // namespace pluginapi

} // namespace soda
