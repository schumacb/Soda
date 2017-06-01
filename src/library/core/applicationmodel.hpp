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
protected:
  QCoreApplication *m_application;
  PluginManager *m_plugin_manager;

public:
  ApplicationModel(QCoreApplication *getApplication, QObject *parent = 0);

  ApplicationModel(const ApplicationModel &other) = delete;
  ApplicationModel &operator=(const ApplicationModel &other) = delete;

  void initialize();

  virtual PluginManager *getPluginManager() const;
  QCoreApplication *getApplication() const;
};
}
