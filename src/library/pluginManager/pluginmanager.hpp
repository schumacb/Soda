#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QCoreApplication>

#include "pluginregistry.hpp"

class PluginManager : public QObject, public PluginRegistry
{
    Q_OBJECT
public:
    explicit PluginManager(QObject *parent = 0);
    void loadPlugins(QStringList plugin_directories);

    // PluginRegistry Interface
    void registerPlugin(PluginInterface &t_plugin);
    PluginInterface *findPlugin(const std::string t_pid, const Version t_version);

private:
    // members
    std::map<std::string, PluginInterface*> m_plugins = {};
    std::multimap<std::string, PluginInterface*> m_deprecated_plugins = {};
    // functions
    void registerDepricatedPlugin(PluginInterface &t_plugin);

signals:

public slots:
};

#endif // PLUGINMANAGER_H
