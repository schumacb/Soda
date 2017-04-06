#include "pluginmanager.hpp"

#include <QDir>
#include <QPluginLoader>

#include <QDebug> // TODO: Remove line
#include <iostream> // TODO: Remove line

#include "plugininterface.hpp"

std::ostream& operator<<(std::ostream& os, const Version& v)
{
    os << v.major << "." << v.minor << "." << v.patch;
    return os;
}

PluginManager::PluginManager(QObject *parent) : QObject(parent)
{
}

void PluginManager::loadPlugins(QCoreApplication *a)
{
    for (QDir pluginsDir : a->libraryPaths()) {
        qDebug() << pluginsDir;
        for (QString fileName : pluginsDir.entryList(QDir::Files)) {
            if (!fileName.toLower().endsWith(".so") && !fileName.toLower().endsWith(".dll")) continue;
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));

            QObject *pluginLoaderInstance = pluginLoader.instance();
            qDebug() << "FileName: " << fileName;
            if(pluginLoaderInstance) {
                PluginInterface *plugin = qobject_cast<PluginInterface *>(pluginLoaderInstance);
                if (plugin)
                {
                    std::cout << "Plugin " << plugin->getName() << " v" << plugin->getVersion() << " loaded." << std::endl;
                } else {
                    qDebug() << "Can't load algorithm plugin";
                }
            }

        }
    }
}

void PluginManager::registerPlugin(PluginInterface *p)
{
    if(p) {
        std::string pid = p->getPid();
        plugins.insert(std::make_pair(pid,p));
    }
}

std::vector<PluginInterface *> PluginManager::findPluginByName(std::__cxx11::string name)
{

}

std::vector<PluginInterface *> PluginManager::findPluginByName(std::__cxx11::string name, Version version, bool exactVersion)
{

}

PluginInterface *PluginManager::finPlugin(std::__cxx11::string pid, Version version)
{

}

