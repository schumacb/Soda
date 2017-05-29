#pragma once

#include <QObject>
#include <QtCore/qglobal.h>

QT_BEGIN_NAMESPACE
class QCoreApplication;
QT_END_NAMESPACE

namespace soda {

class PluginManager;

class ApplicationModel : public QObject {
  Q_OBJECT
private:
  QCoreApplication *m_application;
  PluginManager *m_plugin_manager;

public:
  ApplicationModel(QCoreApplication *application, QObject *parent = 0);

  void initialize();
  PluginManager *pluginManager() const;
  QCoreApplication *application() const;
};
}
