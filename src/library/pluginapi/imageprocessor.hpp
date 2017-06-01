#pragma once

#include <QtCore>
#include <QtPlugin>

#include "node.hpp"

// forward declarations
namespace cv {
class Mat;
}

namespace soda {
namespace pluginapi {

class ImageProcessor : public Node {

public:
  virtual ~ImageProcessor() = default;

public slots:
  virtual void slot_process(cv::Mat mat) = 0;
};

} // pluginapi
} // soda
