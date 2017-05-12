#include "blobdetect.hpp"

#include "exception.hpp"

namespace soda {
namespace plugin {
namespace blobdetect {

using namespace pluginapi;

BlobDetectPlugin::BlobDetectPlugin(QObject *parent) : QObject(parent) {}

const std::string BlobDetectPlugin::getPid() const { return m_pid; }

const QString BlobDetectPlugin::getName() const { return "BlobDetect"; }

const QString BlobDetectPlugin::getDescription() const {
  // TODO: description
  return "";
}

const Version BlobDetectPlugin::getVersion() const {
  return BlobDetectPlugin::m_api_version;
}

void BlobDetectPlugin::onLoad(PluginRegistry &t_registry) {}

void BlobDetectPlugin::onUnload(PluginRegistry &t_registry) {}

BlobDetect::BlobDetect(QString t_id, QObject *t_parent)
    : QObject(t_parent), m_id{t_id} {}

QString BlobDetect::getID() { return m_id; }

} // namespace blobdetect
} // namespace plugin
} // namespace soda
