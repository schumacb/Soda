#include "guiapplicationmodel.hpp"

#include "guipluginmanager.hpp"

using namespace soda;
using namespace soda::ui;

GuiApplicationModel::GuiApplicationModel(QCoreApplication *t_application)
    : ApplicationModel(t_application) {
  m_plugin_manager = new GuiPluginManager(this);
}
