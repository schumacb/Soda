#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QCoreApplication>
#include <QObject>

#include "pluginregistry.hpp"

class PluginManager : public QObject, public PluginRegistry {
  Q_OBJECT
public:
  explicit PluginManager(QObject *parent = 0);
  void loadPlugins(QStringList plugin_directories);

  // PluginRegistry Interface
  void registerPlugin(Plugin &t_plugin);
  Plugin *findPlugin(const std::string t_pid, const Version t_version);

  size_t countRegisteredPlugins() {
    return m_plugins.size() + m_deprecated_plugins.size();
  }

private:
  // members
  std::map<std::string, Plugin *> m_plugins = {};
  std::multimap<std::string, Plugin *> m_deprecated_plugins = {};
  void m_registerDepricatedPlugin(Plugin &t_plugin);

signals:

public slots:
};

#endif // PLUGINMANAGER_H
