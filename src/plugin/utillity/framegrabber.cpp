#include "framegrabber.h"

#include <QJsonDocument>

namespace soda {

namespace plugin {

namespace utillity {

FrameGrabber::FrameGrabber(QObject *parent) : ImageSource(parent) {}

void FrameGrabber::setConfiguration(QJsonDocument configuration) {}

void FrameGrabber::run() {

  if (m_capture.isOpened()) {
    cv::Mat frame;
    m_capture >> frame;
    emit imageReady(frame);

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
