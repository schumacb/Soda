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
    void loadPlugins(QCoreApplication *a);

    // PluginRegistry Interface
    virtual void registerPlugin(PluginInterface *p);
    virtual std::vector<PluginInterface*> findPluginByName(std::string name);
    virtual std::vector<PluginInterface*> findPluginByName(std::string name, Version version, bool exactVersion=false);
    virtual PluginInterface *finPlugin(std::string pid, Version version);

protected:
    std::map<std::string, PluginInterface*> plugins;
    std::multimap<std::string, PluginInterface*> deprecatedPlugins;

signals:

public slots:
};

#endif // PLUGINMANAGER_H
