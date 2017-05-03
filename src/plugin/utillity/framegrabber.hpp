#pragma once

#include <opencv2/videoio.hpp>

#include "imagesource.hpp"

namespace soda {

namespace plugin {

namespace utillity {

class FrameGrabber : public pluginapi::ImageSource {
  Q_OBJECT
protected:
  cv::VideoCapture m_capture{};

public:
  FrameGrabber(QObject *parent = 0);
  bool isOpened();

  // Algorithm interface
public:
  void setConfiguration(const QJsonObject t_config);
  void getConfiguration(QJsonObject &t_config) const;
  void run();
  // ImageSource interface

signals:
  void imageReady(cv::Mat);
};

} // namespace Utillity

} // namespace Plugin

} // namespace Soda
