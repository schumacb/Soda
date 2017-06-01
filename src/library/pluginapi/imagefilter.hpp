#pragma once

#include <QtPlugin>

#include "imageprocessor.hpp"
#include "imagesource.hpp"

namespace soda {
namespace pluginapi {

class ImageFilter : public ImageSource, public ImageProcessor {

public:
  virtual ~ImageFilter() = default;
};

} // namespace pluginapi
} // namespace soda
