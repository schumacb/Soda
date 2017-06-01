#include "corenodesplugin.hpp"

#include "framegrabber.hpp"
#include "imagesender.hpp"
#include "node.hpp"
#include "pluginregistry.hpp"
#include "sodaconfig.hpp"

using namespace soda::pluginapi;
using namespace soda::plugin::corenodes;

CoreNodesPlguin::CoreNodesPlguin(QObject *parent)
    : QObject(parent),
      m_node_factories{new corenodes::FrameGrabberFactory(this),
                       new corenodes::ImageSenderFactory(this)} {}

const soda::pluginapi::Version CoreNodesPlguin::getVersion() const {
  return pluginapi::Version{PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR,
                            PLUGIN_VERSION_PATCH};
}

void CoreNodesPlguin::onLoad(PluginRegistry &t_registry) {
  for (NodeFactory *factory : m_node_factories) {
    t_registry.registerNodeFactory(*factory);
  }
}

void CoreNodesPlguin::onUnload(PluginRegistry &t_registry) {
  // TODO: implement
  Q_UNUSED(t_registry)
}

const QString CoreNodesPlguin::getAuthor() const {
  return Soda_AUTHOR_SCHUMACB;
}

const QString CoreNodesPlguin::getMaintainer() const {
  return Soda_AUTHOR_SCHUMACB;
}

const QString CoreNodesPlguin::getURL() const { return Soda_URL; }
