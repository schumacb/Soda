#pragma once

#include <QObject>

#include <opencv2/videoio.hpp>

#include <imagesource.hpp>

namespace soda {

class FrameGrabber : public QObject {
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
  void signal_imageReady(cv::Mat);
};

} // namespace Soda
