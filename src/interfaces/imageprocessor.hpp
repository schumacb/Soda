#pragma once

// forward declarations
namespace cv {
class Mat;
}

namespace soda {
namespace pluginapi {

class ImageProcessor {

public:
  virtual ~ImageProcessor() {}
  virtual void slot_process(cv::Mat mat) = 0;
};

} // pluginapi
} // soda
