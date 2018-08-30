#pragma once

// Forward declarations
namespace cv {
class Mat;
}

namespace soda {

class ImageSource {

public:
  virtual ~ImageSource() {}
  virtual void signal_imageReady(ImageSource &src) = 0;
};

} // namespace soda
