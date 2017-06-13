#include "corenodesuiplugin.hpp"

#include <nodes/DataModelRegistry>

#include "framegrabbermodel.hpp"
#include "imagepreviewmodel.hpp"
#include "pluginregistry.hpp"
#include "sodaconfig.hpp"

using namespace soda;
using namespace soda::pluginapi;
using namespace soda::plugin::corenodes;

CoreNodesUiPlguin::CoreNodesUiPlguin(QObject *parent) : QObject(parent) {}

const Version CoreNodesUiPlguin::getVersion() const {
  return Version{PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR,
                 PLUGIN_VERSION_PATCH};
}

void CoreNodesUiPlguin::onLoad(PluginRegistry &t_registry) {
  auto *data_model_registry = t_registry.getDataModelRegistry();
  if (data_model_registry == nullptr) {
    return;
  }
  data_model_registry->registerModel<FrameGrabberModel>();
  data_model_registry->registerModel<ImagePreviewModel>();
}

void CoreNodesUiPlguin::onUnload(PluginRegistry &t_registry) {
  Q_UNUSED(t_registry)
}

const QString CoreNodesUiPlguin::getAuthor() const {
  return Soda_AUTHOR_SCHUMACB;
}

const QString CoreNodesUiPlguin::getMaintainer() const {
  return Soda_AUTHOR_SCHUMACB;
}

const QString CoreNodesUiPlguin::getURL() const { return Soda_URL; }
