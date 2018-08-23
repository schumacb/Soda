#include "imagerenderer.hpp"

#include <QJsonObject>

// TODO:Remove
#include <opencv2/highgui.hpp>

namespace soda {
namespace plugin {
namespace utillity {

ImageRenderer::ImageRenderer(QObject *t_parent) : QObject(t_parent) {}

void ImageRenderer::setConfiguration(const QJsonObject t_config) {}

void ImageRenderer::run() {}

void ImageRenderer::slot_process(cv::Mat t_frame) {
  static bool initialized = false;
  if (!initialized) {
    cv::namedWindow("Raw Frame");
  }

  cv::imshow("Raw Frame", t_frame);
}

void ImageRenderer::getConfiguration(QJsonObject &t_config) const {}

} // namespace utillity
} // namespace plugin
} // namespace soda
