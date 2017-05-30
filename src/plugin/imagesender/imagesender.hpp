#pragma once

#include <opencv2/opencv.hpp>

#include <QObject>
#include <QtCore/qglobal.h>

#include "imageprocessor.hpp"
#include "plugin.hpp"
#include "pluginconfig.hpp"

namespace soda {
namespace plugin {
namespace imagesender {

#define ImageSenderPluginID "de.hochschule-trier.soda.plugin.imagesender"

class ImageSenderPlugin;

class ImageSender : public QObject, public pluginapi::ImageProcessor {
  Q_OBJECT
private:
  QString m_id{ImageSenderPluginID};
  pluginapi::Plugin *m_plugin;

public:
  ImageSender(QObject *parent = 0);
  // AlgorithmNode interface
public:
  const QJsonObject &getConfiguration() const override;
  const QString getID() const override;
  pluginapi::Plugin *getPlugin() const override;
  void run() override;
  void setConfiguration(const QJsonObject &configuration) override;
  const char *getSignal(int index) const override;
  const char *getSlot(int index) const override;

  // ImageProcessor interface
public slots:
  void slot_process(cv::Mat mat) override;

  friend ImageSenderPlugin;
};

class ImageSenderFactory : public QObject, public pluginapi::AlgorithmFactory {
private:
  pluginapi::AlgorithmType m_image_sender_type{
      "de.hochschule-trier.soda.plugin.algorithm.imagesender", "", ""};

  // AlgorithmFactory interface
public:
  pluginapi::AlgorithmNode *createAlgorithm(QObject *parent) const override;
  pluginapi::AlgorithmType getAlgorithmType() const override;
};

class ImageSenderPlugin : public QObject, public pluginapi::Plugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID ImageSenderPluginID FILE "imagesender.json")
  Q_INTERFACES(soda::pluginapi::Plugin)

private:
  ImageSenderFactory m_image_sender_factory{};

  // TODO: begin remove
  ImageSender m_image_sender{};

public:
  pluginapi::ImageProcessor &getImageRenderer() { return m_image_sender; }
  // TODO: end remove
  ImageSenderPlugin(QObject *parent = 0);
  ~ImageSenderPlugin() {}

  const std::string getID() const override { return ImageSenderPluginID; }
  const pluginapi::Version getVersion() const override {
    return pluginapi::Version{PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR,
                              PLUGIN_VERSION_PATCH};
  }
  const QString getName() const override;
  const QString getDescription() const override;
  const QString getAuthor() const override;
  const QString getMaintainer() const override;
  const QString getURL() const override;
  void onLoad(pluginapi::PluginRegistry &registry) override;
  void onUnload(pluginapi::PluginRegistry &registry) override;
};

} // namespace imagesender
} // namespace plugin
} // namespace soda
