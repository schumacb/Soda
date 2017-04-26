#ifndef IMAGEFILTER_HPP
#define IMAGEFILTER_HPP

#include "imageprocessor.hpp"
#include "imagesource.hpp"

namespace soda {

namespace pluginapi {

class ImageFilter : public ImageSource, public ImageProcessor {

protected:
  explicit ImageFilter(QObject *parent = 0) : ImageSource(parent) {}

public:
  virtual ~ImageFilter() {}
};

} // namespace pluginapi

} // namespace soda

#endif // IMAGEFILTER_HPP
