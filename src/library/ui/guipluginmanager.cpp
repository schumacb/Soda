#include "guipluginmanager.hpp"

#include "plugin.hpp"

using namespace soda::ui;

void GuiPluginManager::initializePlugins() {
  for (auto plugin : m_plugins) {
    plugin.second->onLoad(*this);
  }
}

GuiPluginManager::GuiPluginManager(QObject *t_parent)
    : PluginManager(t_parent) {}

QtNodes::DataModelRegistry *GuiPluginManager::getDataModelRegistry() {
  return &m_data_model_registry;
}
