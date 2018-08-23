#pragma once

#include "algorithm.hpp"

#include <QtCore>

// Forward declarations
namespace cv {
class Mat;
}

namespace soda {
namespace pluginapi {

class ImageSource : public AlgorithmNode {

public:
  virtual ~ImageSource() {}
signals:
  virtual void signal_imageReady(cv::Mat mat) = 0;
};

} // namespace pluginapi
} // namespace soda
