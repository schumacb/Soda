#pragma once

#include "node.hpp"

#include <QtCore>
#include <QtPlugin>

// Forward declarations
namespace cv {
class Mat;
}

namespace soda {
namespace pluginapi {

class ImageSource : public Node {

public:
  virtual ~ImageSource() = default;
signals:
  virtual void signal_imageReady(cv::Mat mat) = 0;
};

} // namespace pluginapi
} // namespace soda
