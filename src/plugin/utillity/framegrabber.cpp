#include "framegrabber.hpp"

#include <QJsonObject>

namespace soda {

namespace plugin {

namespace utillity {

FrameGrabber::FrameGrabber(QObject *t_parent) : QObject(t_parent) {}

void FrameGrabber::setConfiguration(const QJsonObject t_config) {
  if (!t_config.contains("sourceType")) {
    throw AlgorithmNode::InvalidConfiguration();
  }
  SourceType sourceType = SourceType(t_config["sourceType"].toDouble());
  switch (sourceType) {
  case SourceType::Device:
    break;
  case SourceType::Stream:
    break;
  default:
    throw AlgorithmNode::InvalidConfiguration();
  }
}

void FrameGrabber::getConfiguration(QJsonObject &t_config) const {}

void FrameGrabber::run() {

  if (m_capture.isOpened()) {
    cv::Mat frame;
    m_capture >> frame;
    emit signal_imageReady(frame);

  } else {
    bool open;
    do {
      open = m_capture.open(0);
    } while (!open);
  }
}

} // namespace Utillity

} // namespace Plugin

} // namespace Soda
