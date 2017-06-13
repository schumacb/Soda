#include "corenodesplugin.hpp"

#include "framegrabber.hpp"
#include "imagesender.hpp"
#include "node.hpp"
#include "pluginregistry.hpp"
#include "sodaconfig.hpp"
#include "version.hpp"

using namespace soda;
using namespace soda::pluginapi;
using namespace soda::plugin::corenodes;

CoreNodesPlguin::CoreNodesPlguin(QObject *parent)
    : QObject(parent),
      m_node_factories{new corenodes::FrameGrabberFactory(this),
                       new corenodes::ImageSenderFactory(this)} {}

const Version CoreNodesPlguin::getVersion() const { return m_version; }

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
  return QStringLiteral(Soda_AUTHOR_SCHUMACB);
}

const QString CoreNodesPlguin::getMaintainer() const {
  return QStringLiteral(Soda_AUTHOR_SCHUMACB);
}

const QString CoreNodesPlguin::getURL() const {
  return QStringLiteral(Soda_URL);
}
