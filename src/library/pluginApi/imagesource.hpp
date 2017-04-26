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
  explicit ImageSource(QObject *parrent = 0) : Algorithm(parrent) {}

public:
  virtual ~ImageSource() {}

signals:
  void imageReady(cv::Mat){};
};

} // namespace pluginapi

} // namespace soda

#endif // IMAGESOURCE_HPP
