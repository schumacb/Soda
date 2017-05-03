#pragma once

#include <QObject>
#include <QRunnable>

namespace soda {

namespace pluginapi {

class AlgorithmNode : public QObject {

protected:
  AlgorithmNode(QObject *parent = 0) : QObject(parent) {}

public:
  virtual ~AlgorithmNode() {}
  virtual void setConfiguration(const QJsonObject) = 0;
  virtual void getConfiguration(QJsonObject &) const = 0;
  // Exceptions
  class InvalidConfiguration {};

public slots:
  virtual void run() = 0;
};

} // namespace pluginapi

} // namespace soda
