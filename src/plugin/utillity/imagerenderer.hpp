#ifndef FRAMERENDERER_HPP
#define FRAMERENDERER_HPP

#include <QtCore/qglobal.h>

#include "imageprocessor.hpp"

namespace soda {
namespace plugin {
namespace utillity {

class ImageRenderer : public pluginapi::ImageProcessor {
  Q_OBJECT
public:
  ImageRenderer(QObject *parent = 0);

  // Algorithm interface
public:
  void setConfiguration(QJsonDocument configuration);

public slots:
  void run();
  void process(cv::Mat);
};

} // namespace utilltiy
} // namespace plugin
} // namespace soda

#endif // FRAMERENDERER_HPP
