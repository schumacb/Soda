#include "imagerenderer.hpp"

#include <QJsonObject>

// TODO:Remove
#include <opencv2/highgui.hpp>

#include "exception.hpp"

namespace soda {
namespace plugin {
namespace framegrabber {

ImageRenderer::ImageRenderer(QString id, QObject *t_parent)
    : QObject(t_parent), m_id{id} {}

void ImageRenderer::setConfiguration(const QJsonObject &t_config) {
  // TODO: implement
  Q_UNUSED(t_config)
}

void ImageRenderer::run() {}

void ImageRenderer::slot_process(cv::Mat t_frame) {
  static bool initialized = false;
  if (!initialized) {
    cv::namedWindow("Raw Frame");
  }

  cv::imshow("Raw Frame", t_frame);
}

const QJsonObject &ImageRenderer::getConfiguration() const {
  // TODO: implement
  throw NotYetImplemented();
}

QString ImageRenderer::getID() { return m_id; }

} // namespace utillity
} // namespace plugin
} // namespace soda
