#pragma once

#include <QObject>

#include "plugin.hpp"
#include "pluginconfig.hpp"
#include "version.hpp"

namespace soda {
namespace plugin {
namespace corenodes {

#define CoreNodesUiPluginID "de.hochschule-trier.soda.plugin.corenodesui"

class CoreNodesUiPlguin : public QObject, public pluginapi::Plugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID CoreNodesUiPluginID FILE "corenodesui.json")
  Q_INTERFACES(soda::pluginapi::Plugin)

private:
public:
  // TODO: end remove
  CoreNodesUiPlguin(QObject *parent = 0);
  ~CoreNodesUiPlguin() {}

  const std::string getID() const override { return CoreNodesUiPluginID; }
  const Version getVersion() const override;
  const QString getName() const override { return "CoreNodesUi"; }
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
