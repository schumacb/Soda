#include "imagerenderer.hpp"

#include <QJsonDocument>

// TODO:Remove
#include <opencv2/highgui.hpp>

namespace soda {
namespace plugin {
namespace utillity {

ImageRenderer::ImageRenderer(QObject *parent) { cv::namedWindow("Raw Frame"); }

void ImageRenderer::setConfiguration(QJsonDocument configuration) {}

void ImageRenderer::run() {}

void ImageRenderer::process(cv::Mat frame) { cv::imshow("Raw Frame", frame); }

} // namespace utillity
} // namespace plugin
} // namespace soda
