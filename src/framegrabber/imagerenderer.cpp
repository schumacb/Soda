#include "imagerenderer.hpp"

#include <QJsonObject>

// TODO:Remove
#include <opencv2/highgui.hpp>

namespace soda {

ImageRenderer::ImageRenderer(QObject *t_parent) : QObject(t_parent) {}

void ImageRenderer::setConfiguration(const QJsonObject t_config)
{}

void ImageRenderer::run() {}

void ImageRenderer::slot_process(cv::Mat matrix) {
  static bool initialized = false;
  if (!initialized) {
    cv::namedWindow("Raw Frame");
  }

  cv::imshow("Raw Frame", matrix);
}

void ImageRenderer::getConfiguration(QJsonObject& t_config) const
{}

} // namespace soda
