#pragma once

#include <opencv2/opencv.hpp>

#include <QObject>
#include <QtCore/qglobal.h>

#include "imageprocessor.hpp"
#include "nodetype.hpp"
#include "plugin.hpp"
#include "pluginconfig.hpp"

namespace soda {
namespace plugin {
namespace corenodes {

class CoreNodesPlugin;
class ImageSenderFactory;

class ImageSender : public QObject, public pluginapi::ImageProcessor {
  Q_OBJECT
private:
  static const NodeType TYPE;
  static int instance_count;
  std::string m_window_name{""};

public:
  ImageSender(QObject *parent = 0);
  // Node interface
public:
  const QJsonObject getConfiguration() const override;
  const NodeType &getType() const override;
  void setConfiguration(const QJsonObject &configuration) override;
  const char *getSignal(int index) const override;
  const char *getSlot(int index) const override;
  void run() override;

  // ImageProcessor interface
public slots:
  void slot_process(cv::Mat mat) override;

  friend CoreNodesPlugin;
  friend ImageSenderFactory;
};

class ImageSenderFactory : public QObject, public pluginapi::NodeFactory {
  Q_OBJECT
  // AlgorithmFactory interface
public:
  explicit ImageSenderFactory(QObject *parent = 0);
  pluginapi::Node *createNode(QObject *parent) const override;
  const NodeType &getType() const override;
};

} // namespace corenodes
} // namespace plugin
} // namespace soda
