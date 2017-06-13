#include "applicationmodel.hpp"

#include <QCoreApplication>

#include "pluginmanager.hpp"

using namespace soda;

ApplicationModel::ApplicationModel(QCoreApplication *t_application,
                                   QObject *t_parent)
    : QObject(t_parent), m_application{t_application},
      m_plugin_manager{new PluginManager(this)} {
  m_application->addLibraryPath(
      QCoreApplication::applicationDirPath() +
      "/../lib"); // TODO: move to setting default plugin path
}

void ApplicationModel::initialize() {
  auto libPaths = m_application->libraryPaths();
  m_plugin_manager->loadPlugins(libPaths);
}

PluginManager *ApplicationModel::getPluginManager() const {
  return m_plugin_manager;
}

QCoreApplication *ApplicationModel::getApplication() const {
  return m_application;
}
