#include "pluginmanager.hpp"

#include <QDir>
#include <QPluginLoader>

#include <QDebug> // TODO: Remove line

#include "plugin.hpp"

namespace soda {
namespace pluginmanager {

using namespace pluginapi;

PluginManager::PluginManager(QObject *parent) : QObject(parent) {}

// TODO: Check interface version

void PluginManager::loadPlugins(QStringList plugin_directories) {
  for (QDir pluginsDir : plugin_directories) {
    qDebug() << pluginsDir;
    for (QString fileName : pluginsDir.entryList(QDir::Files)) {
      if (!fileName.toLower().endsWith(".so") &&
          !fileName.toLower().endsWith(".dll")) {
        continue;
      }
      auto *pluginLoader =
          new QPluginLoader(pluginsDir.absoluteFilePath(fileName), this);

      QObject *pluginLoaderInstance = pluginLoader->instance();
      if (!pluginLoaderInstance) {
        continue;
      }

      if (Plugin *plugin = qobject_cast<Plugin *>(pluginLoaderInstance)) {
        registerPlugin(*plugin);
      }
    }
  }
}

void PluginManager::registerPlugin(Plugin &t_plugin) {
  auto pid = t_plugin.getPid();
  auto it = m_plugins.find(pid);
  auto pair = std::make_pair(pid, &t_plugin);
  if (m_plugins.empty() || it == m_plugins.end()) { // plugin not yet registered
    m_plugins.insert(pair);
  } else { // plugin already registered
    auto plugin = it->second;
    if (t_plugin.getVersion() > plugin->getVersion()) {
      // register newer version
      it->second = &t_plugin;
    }
  }
}

Plugin *PluginManager::findPlugin(const std::string &t_pid,
                                  const Version &t_version) {
  auto plugins_it = m_plugins.find(t_pid);

  if (plugins_it != m_plugins.end() &&
      plugins_it->second->getVersion() == t_version) {
    return plugins_it->second;
  }

  return nullptr;
}

void PluginManager::registerAlgorithm(AlgorithmFactory &t_factory) {
  auto id = t_factory.getAlgorithmType().id;
  auto it = m_algorithms.find(id);
  auto pair = std::make_pair(id, &t_factory);
  // register only when algo not yet registered
  if (m_algorithms.empty() || it == m_algorithms.end()) {
    m_algorithms.insert(pair);
  }
}

} // pluginmanager
} // soda
