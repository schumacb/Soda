#pragma once

#include <QtCore>

#include "algorithm.hpp"

// forward declarations
namespace cv {
class Mat;
}

namespace soda {
namespace pluginapi {

class ImageProcessor : public AlgorithmNode {

public:
  virtual ~ImageProcessor() {}

public slots:
  virtual void slot_process(cv::Mat mat) = 0;
};

} // pluginapi
} // soda
