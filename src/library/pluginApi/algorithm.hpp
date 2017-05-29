#pragma once

#include <memory>
#include <string>

#include <QString>
#include <QUuid>

QT_BEGIN_NAMESPACE
class QObject;
class QJsonObject;
QT_END_NAMESPACE

namespace soda {
namespace pluginapi {

class AlgorithmType {
public:
  const std::string id;
  QString name;
  QString description;

  bool operator==(const AlgorithmType &t_other) const {
    return id == t_other.id;
  }
};

class AlgorithmNode {
public:
  virtual ~AlgorithmNode() {}
  virtual QString getID() = 0;
  virtual void setConfiguration(const QJsonObject &configuration) = 0;
  virtual const QJsonObject &getConfiguration() const = 0;
  virtual void run() = 0;

  // Exceptions
  class InvalidConfiguration {};
};

class AlgorithmFactory {
public:
  virtual ~AlgorithmFactory() {}
  virtual AlgorithmNode *createAlgorithm(QObject *parent = 0) const = 0;
  virtual AlgorithmType getAlgorithmType() const = 0;
};

} // namespace pluginapi
} // namespace soda
