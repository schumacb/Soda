#pragma once

// Forward declarations
namespace cv {
class Mat;
}

namespace soda {

class ImageSource {

public:
  virtual ~ImageSource() {}
  virtual void signal_imageReady(cv::Mat mat) = 0;
};

} // namespace soda
