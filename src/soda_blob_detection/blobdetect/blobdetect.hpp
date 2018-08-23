#pragma once

#include <QObject>
#include <QtPlugin>

#include <opencv2/opencv.hpp>

#include "plugin.hpp"

#include "pluginconfig.hpp"

#define BlobDetectPluginID "de.hochschule-trier.soda.plugin.blobdetect"

namespace soda {

namespace plugin {

namespace blobdetect {

class BlobDetect : public QObject, public Plugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID BlobDetectPluginID FILE "blobdetect.json")
  Q_INTERFACES(Plugin)
protected:
  const std::string PID = BlobDetectPluginID;
  static constexpr Version VERSION = {
      PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_PATCH};
  const std::string NAME = "BlobDetect";
  const std::string DESCRIPTION = "TODO"; // TODO: Describe Plugin.

public:
  explicit BlobDetect(QObject *parent = 0);

  const std::string getPid() const override { return PID; }
  const Version getVersion() const override { return BlobDetect::VERSION; }
  const std::string getName() const override { return NAME; }
  const std::string getDescription() const override { return DESCRIPTION; }

  void onLoad() override;
  void onUnload() override;
};

} // namespace BlobDetect

} // namespace Plugin

} // namespace Soda
