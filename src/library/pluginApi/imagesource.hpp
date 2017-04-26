#ifndef IMAGESOURCE_HPP
#define IMAGESOURCE_HPP

#include "algorithm.hpp"

// Forward declaration
namespace cv {
class Mat;
}

namespace soda {

namespace pluginapi {

class ImageSource : public Algorithm {

protected:
  explicit ImageSource(QObject *parent = 0) : Algorithm(parent) {}

public:
  virtual ~ImageSource() {}

signals:
  void imageReady(cv::Mat){};
};

} // namespace pluginapi

} // namespace soda

#endif // IMAGESOURCE_HPP
