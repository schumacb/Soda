#pragma once

#include <QtCore/qglobal.h>

QT_BEGIN_NAMESPACE
class QJsonObject;
QT_END_NAMESPACE

namespace soda {

class PluginManager;

class FlowSceneParser {
private:
  PluginManager *m_plugin_manager;

public:
  FlowSceneParser(PluginManager *t_plugin_manager);

  void parse(const QJsonObject &object);
};

} // namespace soda
