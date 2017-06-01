#pragma once

#include <QObject>

#include "node.hpp"
#include "plugin.hpp"
#include "pluginconfig.hpp"
#include "version.hpp"

namespace soda {
namespace plugin {
namespace corenodes {

#define CoreNodesPluginID "de.hochschule-trier.soda.plugin.corenodes"

class CoreNodesPlguin : public QObject, public pluginapi::Plugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID CoreNodesPluginID FILE "corenodesplugin.json")
  Q_INTERFACES(soda::pluginapi::Plugin)

private:
  std::vector<pluginapi::NodeFactory *> m_node_factories;

public:
  // TODO: end remove
  CoreNodesPlguin(QObject *parent = 0);
  ~CoreNodesPlguin() {}

  const std::string getID() const override { return CoreNodesPluginID; }
  const pluginapi::Version getVersion() const override;
  const QString getName() const override { return "CoreNodes"; }
  const QString getDescription() const override {
    return "DESCRIPTION";
  } // TODO: Describe Plugin.

  void onLoad(pluginapi::PluginRegistry &registry) override;
  void onUnload(pluginapi::PluginRegistry &registry) override;

  // Plugin interface
public:
  const QString getAuthor() const override;
  const QString getMaintainer() const override;
  const QString getURL() const override;
};

} // namespace corenodes
} // namespace plugin
} // namespace soda
