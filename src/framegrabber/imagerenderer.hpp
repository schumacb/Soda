#pragma once

#include <QObject>
#include <QtCore/qglobal.h>
#include <opencv2/highgui.hpp>
#include <imageprocessor.hpp>

namespace soda {

class ImageRenderer : public QObject, public pluginapi::ImageProcessor {
  Q_OBJECT
public:
  ImageRenderer(QObject *parent = 0);

  // Algorithm interface
  void getConfiguration(QJsonObject &) const;
  void run();
  void setConfiguration(const QJsonObject);

  // ImageProcessor interface
public slots:
  void slot_process(cv::Mat matrix);
};

} // namespace soda
