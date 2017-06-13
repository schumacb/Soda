#pragma once

#include <QObject>
#include <QUuid>

#include "node.hpp"
#include "pluginregistry.hpp"
#include "version.hpp"

namespace soda {

class PluginManager : public QObject, public pluginapi::PluginRegistry {
  Q_OBJECT
private:
  virtual void initializePlugins();

protected:
  std::map<std::string, pluginapi::Plugin *> m_plugins{};
  std::map<std::string, pluginapi::NodeFactory *> m_algorithms{};
  std::map<QUuid, pluginapi::Node *> m_nodes{};

public:
  explicit PluginManager(QObject *parent = 0);

  virtual void loadPlugins(QStringList plugin_directories);
  pluginapi::Node *getNode(const QUuid uuid);
  pluginapi::Node *createNode(const QUuid uuid, const QString pid);

  // PluginRegistry Interface
  void registerPlugin(pluginapi::Plugin &t_plugin) override;
  pluginapi::Plugin *findPlugin(const std::string &t_pid,
                                const Version &t_version) override;
  void registerNodeFactory(pluginapi::NodeFactory &factory) override;

  size_t countRegisteredPlugins() { return m_plugins.size(); }
  virtual QtNodes::DataModelRegistry *getDataModelRegistry() override;
};

} // soda
