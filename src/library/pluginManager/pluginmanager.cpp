#include "pluginmanager.hpp"

#include <QDir>
#include <QPluginLoader>

#include <QDebug>   // TODO: Remove line
#include <iostream> // TODO: Remove line

#include "plugininterface.hpp"

std::ostream &operator<<(std::ostream &os, const Version &v) {
  os << v.major << "." << v.minor << "." << v.patch;
  return os;
}

bool operator<(const Version &v1, const Version &v2) {
  return (v1.major < v2.major) ||
         (v1.major == v2.major && v1.minor < v2.minor) ||
         (v1.major == v2.major && v1.minor == v2.minor && v1.patch < v2.patch);
}

bool operator>(const Version &v1, const Version &v2) {
  return (v1.major > v2.major) ||
         (v1.major == v2.major && v1.minor > v2.minor) ||
         (v1.major == v2.major && v1.minor == v2.minor && v1.patch > v2.patch);
}

bool operator==(const Version &v1, const Version &v2) {
  return (v1.major == v2.major && v1.minor == v2.minor && v1.patch == v2.patch);
}

PluginManager::PluginManager(QObject *parent) : QObject(parent) {}

void PluginManager::loadPlugins(QStringList plugin_directories) {
  for (QDir pluginsDir : plugin_directories) {
    for (QString fileName : pluginsDir.entryList(QDir::Files)) {
      if (!fileName.toLower().endsWith(".so") &&
          !fileName.toLower().endsWith(".dll")) {
        continue;
      }
      QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));

      QObject *pluginLoaderInstance = pluginLoader.instance();
      if (!pluginLoaderInstance) {
          continue;
      }
      PluginInterface *plugin =
          qobject_cast<PluginInterface *>(pluginLoaderInstance);
      if (plugin) {
        registerPlugin(*plugin);
      }
    }
  }
}

void PluginManager::registerPlugin(PluginInterface &t_plugin) {
  auto pid = t_plugin.getPid();
  auto it = m_plugins.find(pid);
  auto pair = std::make_pair(pid, &t_plugin);
  if (m_plugins.empty() || it == m_plugins.end()) { // plugin not yet registered
    m_plugins.insert(pair);
  } else { // plugin already registered
    auto plugin = it->second;
    if (t_plugin.getVersion() > plugin->getVersion()) {
        // newer version
        registerDepricatedPlugin(*plugin);
        it->second = &t_plugin;
    } else if(t_plugin.getVersion() < plugin->getVersion()) {
        // older version
        registerDepricatedPlugin(t_plugin);
    }
  }
}

void PluginManager::registerDepricatedPlugin(PluginInterface &t_plugin)
{
    auto pid = t_plugin.getPid();
    auto it = m_deprecated_plugins.find(pid);
    auto pair = std::make_pair(pid, &t_plugin);
    if (m_deprecated_plugins.empty() || it == m_deprecated_plugins.end()) { // plugin not yet registered
      m_deprecated_plugins.insert(pair);
    } else { // plugin already registered
      auto plugin = it->second;
      if (plugin->getVersion() == t_plugin.getVersion()) {
          // same version
          return;
      } else {
          m_deprecated_plugins.insert(pair);
      }
    }
}

PluginInterface *PluginManager::findPlugin(const std::string t_pid,
                                          const Version t_version) {
    auto plugins_it = m_plugins.find(t_pid);
    auto deprecated_plugins_range = m_deprecated_plugins.equal_range(t_pid);
    if (plugins_it != m_plugins.end() && plugins_it->second->getVersion() == t_version) {
        return plugins_it->second;
    }
    if (deprecated_plugins_range.first != m_deprecated_plugins.end()) {
        for (auto it=deprecated_plugins_range.first;it!=deprecated_plugins_range.second; ++it){
            if(it->second->getVersion() == t_version) {
              return it->second;
            }
        }
    }
    return nullptr;
}
