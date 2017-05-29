#pragma once

#include <QObject>
#include <QUuid>

#include "algorithm.hpp"
#include "pluginregistry.hpp"
#include "version.hpp"

namespace soda {

class PluginManager : public QObject, public pluginapi::PluginRegistry {
  Q_OBJECT
private:
  // members
  std::map<std::string, pluginapi::Plugin *> m_plugins{};
  std::map<std::string, pluginapi::AlgorithmFactory *> m_algorithms{};
  std::map<QUuid, pluginapi::AlgorithmNode *> m_nodes{};

public:
  explicit PluginManager(QObject *parent = 0);

  void loadPlugins(QStringList plugin_directories);
  pluginapi::AlgorithmNode *getNode(const QUuid uuid);
  pluginapi::AlgorithmNode *createNode(const QUuid uuid, const QString pid);

  // PluginRegistry Interface
  void registerPlugin(pluginapi::Plugin &t_plugin) override;
  pluginapi::Plugin *findPlugin(const std::string &t_pid,
                                const pluginapi::Version &t_version) override;
  void registerAlgorithm(pluginapi::AlgorithmFactory &factory) override;

  size_t countRegisteredPlugins() { return m_plugins.size(); }

signals:

public slots:
};

} // soda
