#pragma once

#include <QtCore/qglobal.h>

#include "imageprocessor.hpp"

namespace soda {
namespace plugin {
namespace utillity {

class ImageRenderer : public pluginapi::ImageProcessor {
  Q_OBJECT
public:
  ImageRenderer(QObject *parent = 0);

public slots:
  void run();
  void process(cv::Mat);

  // Algorithm interface
public:
  void setConfiguration(const QJsonObject);
  void getConfiguration(QJsonObject &) const;
};

} // namespace utilltiy
} // namespace plugin
} // namespace soda
