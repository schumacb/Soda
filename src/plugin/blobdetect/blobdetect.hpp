#pragma once

#include <QObject>
#include <QtPlugin>

#include <opencv2/opencv.hpp>

#include "node.hpp"
#include "nodetype.hpp"
#include "plugin.hpp"
#include "pluginconfig.hpp"
#include "sodaconfig.hpp"
#include "version.hpp"

#define BlobDetectPluginID "de.hochschule-trier.soda.plugin.blobdetect"
#define BlobDetectNodeID "de.hochschule-trier.soda.node.blobdetect"

namespace soda {
namespace plugin {
namespace blobdetect {

class BlobDetect : public QObject, public pluginapi::Node {
  Q_OBJECT
public:
  static const NodeType TYPE;
  explicit BlobDetect(QObject *parent = 0);

  // Node interface
public:
  void setConfiguration(const QJsonObject &configuration) override;
  const QJsonObject getConfiguration() const override;

  void run() override;

  // Node interface
public:
  const NodeType &getType() const override;
  const char *getSignal(int index) const override;
  const char *getSlot(int index) const override;
};

class BlobDetectPlugin : public QObject, public pluginapi::Plugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID BlobDetectPluginID FILE "blobdetect.json")
  Q_INTERFACES(soda::pluginapi::Plugin)

private:
  static constexpr Version API_VERSION{
      PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_PATCH};

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
  const Version getVersion() const override;
  void onLoad(pluginapi::PluginRegistry &registry) override;
  void onUnload(pluginapi::PluginRegistry &registry) override;
};

} // namespace blobdetect
} // namespace plugin
} // namespace soda
