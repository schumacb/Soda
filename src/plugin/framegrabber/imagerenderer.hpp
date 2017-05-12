#pragma once

#include <opencv2/opencv.hpp>

#include <QObject>
#include <QtCore/qglobal.h>

#include "imageprocessor.hpp"

namespace soda {
namespace plugin {
namespace framegrabber {

class ImageRenderer : public QObject, public pluginapi::ImageProcessor {
  Q_OBJECT
private:
  QString m_id;

public:
  ImageRenderer(QString id, QObject *parent = 0);

  // Algorithm interface
  const QJsonObject &getConfiguration() const override;
  QString getID() override;
  void run() override;
  void setConfiguration(const QJsonObject &configuration) override;

  // ImageProcessor interface
public slots:
  void slot_process(cv::Mat mat) override;
};

} // namespace utilltiy
} // namespace plugin
} // namespace soda
