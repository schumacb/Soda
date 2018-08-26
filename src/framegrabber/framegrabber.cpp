#include "framegrabber.hpp"

#include <QJsonObject>

namespace soda {

FrameGrabber::FrameGrabber(QObject *t_parent) : QObject(t_parent) {}

void FrameGrabber::setConfiguration(const QJsonObject t_config)
{}

void FrameGrabber::getConfiguration(QJsonObject& t_config) const
{}

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

} // namespace Soda
