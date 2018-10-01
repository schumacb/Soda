#pragma once

namespace soda {

class ImageSource {

public:
  virtual ~ImageSource();
  virtual void signal_imageReady(ImageSource &src) = 0;
};

} // namespace soda
