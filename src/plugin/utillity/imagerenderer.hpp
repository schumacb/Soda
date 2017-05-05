#pragma once

#include <opencv2/opencv.hpp>

#include <QObject>
#include <QtCore/qglobal.h>

#include "imageprocessor.hpp"

namespace soda {
namespace plugin {
namespace utillity {

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
  void slot_process(cv::Mat mat);
};

} // namespace utilltiy
} // namespace plugin
} // namespace soda
