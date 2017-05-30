#pragma once

#include <QObject>
#include <QtPlugin>

#include <opencv2/opencv.hpp>

#include "algorithm.hpp"
#include "plugin.hpp"

#include "pluginconfig.hpp"

#define BlobDetectPluginID "de.hochschule-trier.soda.plugin.blobdetect"

namespace soda {
namespace plugin {
namespace blobdetect {

class BlobDetect : public QObject, public pluginapi::AlgorithmNode {

private:
  const QString m_id{};

public:
  explicit BlobDetect(QString id, QObject *parent = 0);

  // AlgorithmNode interface
public:
  const QString getID() const override;
  void setConfiguration(const QJsonObject &configuration) override;
  const QJsonObject &getConfiguration() const override;
  void run() override;
};

class BlobDetectPlugin : public QObject, public pluginapi::Plugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID BlobDetectPluginID FILE "blobdetect.json")
  Q_INTERFACES(soda::pluginapi::Plugin)

private:
  const std::string m_pid = BlobDetectPluginID;
  static constexpr pluginapi::Version m_api_version = {
      PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_PATCH};
  const pluginapi::AlgorithmType m_blobdetect_type{"BlobDetect", "", ""};

public:
  explicit BlobDetectPlugin(QObject *parent = 0);

  // Plugin interface
public:
  const std::string getID() const override;
  const QString getName() const override;
  const QString getDescription() const override;
  const QString getAuthor() const override;
  const QString getMaintainer() const override;
  const QString getURL() const override;
  const pluginapi::Version getVersion() const override;
  void onLoad(pluginapi::PluginRegistry &registry) override;
  void onUnload(pluginapi::PluginRegistry &registry) override;
};

} // namespace blobdetect
} // namespace plugin
} // namespace soda
