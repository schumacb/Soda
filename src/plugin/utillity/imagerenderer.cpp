#include "imagerenderer.hpp"

#include <QJsonObject>

// TODO:Remove
#include <opencv2/highgui.hpp>

namespace soda {
namespace plugin {
namespace utillity {

ImageRenderer::ImageRenderer(QObject *t_parent) {
  cv::namedWindow("Raw Frame");
}

void ImageRenderer::setConfiguration(const QJsonObject t_config) {}

void ImageRenderer::run() {}

void ImageRenderer::process(cv::Mat t_frame) {
  cv::imshow("Raw Frame", t_frame);
}

void ImageRenderer::getConfiguration(QJsonObject &t_config) const {}

} // namespace utillity
} // namespace plugin
} // namespace soda
