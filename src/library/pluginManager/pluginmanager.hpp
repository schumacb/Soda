#pragma once

#include <QObject>

#include "pluginregistry.hpp"
#include "version.hpp"

namespace soda {
namespace pluginmanager {

class PluginManager : public QObject, public pluginapi::PluginRegistry {
  Q_OBJECT
private:
  // members
  std::map<std::string, pluginapi::Plugin *> m_plugins{};
  std::map<std::string, pluginapi::AlgorithmFactory *> m_algorithms{};

public:
  explicit PluginManager(QObject *parent = 0);

  void loadPlugins(QStringList plugin_directories);

  // PluginRegistry Interface
  void registerPlugin(pluginapi::Plugin &t_plugin) override;
  pluginapi::Plugin *findPlugin(const std::string &t_pid,
                                const pluginapi::Version &t_version) override;
  void registerAlgorithm(pluginapi::AlgorithmFactory &factory) override;

  size_t countRegisteredPlugins() { return m_plugins.size(); }

signals:

public slots:
};

} // pluginmanager
} // soda
