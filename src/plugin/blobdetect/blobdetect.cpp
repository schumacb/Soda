#include "blobdetect.hpp"

#include "exception.hpp"
#include "sodaconfig.hpp"

using namespace soda;
using namespace soda::pluginapi;
using namespace soda::plugin::blobdetect;

BlobDetectPlugin::BlobDetectPlugin(QObject *parent) : QObject(parent) {}

const std::string BlobDetectPlugin::getID() const { return m_pid; }

const QString BlobDetectPlugin::getName() const { return "BlobDetect"; }

const QString BlobDetectPlugin::getDescription() const {
  // TODO: description
  return "";
}

const QString BlobDetectPlugin::getAuthor() const {
  return Soda_AUTHOR_SCHUMACB;
}

const QString BlobDetectPlugin::getMaintainer() const {
  return Soda_AUTHOR_SCHUMACB;
}

const QString BlobDetectPlugin::getURL() const { return Soda_URL; }

const Version BlobDetectPlugin::getVersion() const {
  return BlobDetectPlugin::m_api_version;
}

void BlobDetectPlugin::onLoad(PluginRegistry &t_registry) {
  // TODO: implement
  Q_UNUSED(t_registry)
}

void BlobDetectPlugin::onUnload(PluginRegistry &t_registry) {
  // TODO: implement
  Q_UNUSED(t_registry)
}

const NodeType BlobDetect::TYPE = NodeType(
    "de.hochschule-trier.soda.plugin.node.blobdetect", "BlobDetect", "");
// TODO: Describe Type

BlobDetect::BlobDetect(QObject *t_parent) : QObject(t_parent) {}

void BlobDetect::setConfiguration(const QJsonObject &t_configuration) {
  Q_UNUSED(t_configuration)
  // TODO: read config
}

const QJsonObject BlobDetect::getConfiguration() const {
  QJsonObject config;
  // TODO: write config
  return config;
}

void BlobDetect::run() {}

const NodeType &BlobDetect::getType() const { return BlobDetect::TYPE; }

const char *BlobDetect::getSignal(int t_index) const {
  Q_UNUSED(t_index)
  return "";
}

const char *BlobDetect::getSlot(int t_index) const {
  Q_UNUSED(t_index)
  return "";
}
