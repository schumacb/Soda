#pragma once

#include <QtCore/qglobal.h>

#include <nodes/DataModelRegistry>

#include "pluginmanager.hpp"

namespace soda {
namespace ui {

class GuiPluginManager : public PluginManager {
private:
  QtNodes::DataModelRegistry m_data_model_registry{};

  void initializePlugins() override;

public:
  explicit GuiPluginManager(QObject *parent);

  // PluginRegistry interface
public:
  QtNodes::DataModelRegistry *getDataModelRegistry() override;
};

} // ui
} // soda
