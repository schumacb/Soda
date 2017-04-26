#ifndef IMAGEPROCESSOR_HPP
#define IMAGEPROCESSOR_HPP

#include "algorithm.hpp"

// forward declaration
namespace cv {
class Mat;
}

namespace soda {

namespace pluginapi {

class ImageProcessor : public Algorithm {

protected:
  explicit ImageProcessor(QObject *parent = 0) : Algorithm(parent) {}

public:
  virtual ~ImageProcessor() {}

public slots:
  void process(cv::Mat);
};

} // pluginapi

} // soda

#endif // IMAGEPORCESSOR_HPP
