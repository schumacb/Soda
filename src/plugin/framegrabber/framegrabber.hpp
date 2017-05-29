#pragma once

#include <QObject>
#include <QtPlugin>

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

#include "imagesource.hpp"
#include "plugin.hpp"
#include "pluginconfig.hpp"

namespace soda {
namespace plugin {
namespace framegrabber {

#define FrameGrabberPluginID "de.hochschule-trier.soda.plugin.framegrabber"

class FrameGrabber : public QObject, public pluginapi::ImageSource {
  Q_OBJECT

private:
  cv::VideoCapture m_capture{};
  QString m_id{FrameGrabberPluginID};
  int m_device{0};
  cv::String m_url{""};

public:
  enum SourceType { Device, Stream };

  FrameGrabber(QObject *parent = 0);
  bool isOpened();

  // Algorithm interface
public:
  void setConfiguration(const QJsonObject &t_config) override;
  const QJsonObject &getConfiguration() const override;
  QString getID() override;
  void run() override;
  // ImageSource interface
signals:
  void signal_imageReady(cv::Mat) override;
};

class FrameGrabberFactory : public QObject, public pluginapi::AlgorithmFactory {
private:
  pluginapi::AlgorithmType m_framegrabber_type{
      "de.hochschule-trier.soda.plugin.algorithm.framegrabber", "", ""};

  // AlgorithmFactory interface
public:
  pluginapi::AlgorithmNode *createAlgorithm(QObject *parent) const override;
  pluginapi::AlgorithmType getAlgorithmType() const override;
};

class FrameGrabberPlugin : public QObject, public pluginapi::Plugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID FrameGrabberPluginID FILE "framegrabber.json")
  Q_INTERFACES(soda::pluginapi::Plugin)

private:
  FrameGrabberFactory m_frame_grabber_factory{};

  // TODO: begin remove
  FrameGrabber m_frame_grabber{};

public:
  pluginapi::ImageSource &getFrameGrabber() { return m_frame_grabber; }
  // TODO: end remove
  FrameGrabberPlugin(QObject *parent = 0);
  ~FrameGrabberPlugin() {}

  const std::string getPid() const override { return FrameGrabberPluginID; }
  const pluginapi::Version getVersion() const override {
    return pluginapi::Version{PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR,
                              PLUGIN_VERSION_PATCH};
  }
  const QString getName() const override { return "Utillity"; }
  const QString getDescription() const override {
    return "DESCRIPTION";
  } // TODO: Describe Plugin.

  void onLoad(pluginapi::PluginRegistry &registry) override;
  void onUnload(pluginapi::PluginRegistry &registry) override;
};

} // namespace framegrabber
} // namespace plugin
} // namespace soda
