#pragma once

#include <QObject>
#include <QtPlugin>

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

#include "imagesource.hpp"
#include "nodetype.hpp"
#include "plugin.hpp"
#include "pluginconfig.hpp"

namespace soda {
namespace plugin {
namespace corenodes {

class CoreNodesPlguin;
class FrameGrabberFactory;

class FrameGrabber : public QObject, public pluginapi::ImageSource {
  Q_OBJECT

private:
  static const NodeType TYPE;
  cv::VideoCapture m_capture{};
  int m_device{0};
  cv::String m_url{""};

public:
  enum SourceType { Device, Stream };

  FrameGrabber(QObject *parent = 0);
  void run() override;
  bool isOpened();

  // Node interface
public:
  void setConfiguration(const QJsonObject &t_config) override;
  const QJsonObject getConfiguration() const override;

  const NodeType &getType() const override;

  const char *getSignal(int index) const override;
  const char *getSlot(int index) const override;
  // ImageSource interface
signals:
  void signal_imageReady(cv::Mat) override;

  friend FrameGrabberFactory;
};

class FrameGrabberFactory : public QObject, public pluginapi::NodeFactory {
  Q_OBJECT
public:
  explicit FrameGrabberFactory(QObject *parent = 0);
  // AlgorithmFactory interface
  pluginapi::Node *createNode(QObject *parent) const override;
  const NodeType &getType() const override;
};

} // namespace corenodes
} // namespace plugin
} // namespace soda
