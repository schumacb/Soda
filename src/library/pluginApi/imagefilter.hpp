#pragma once

#include "imageprocessor.hpp"
#include "imagesource.hpp"

namespace soda {
namespace pluginapi {

class ImageFilter : public ImageSource, public ImageProcessor {

public:
  virtual ~ImageFilter() {}
};

} // namespace pluginapi
} // namespace soda
