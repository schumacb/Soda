#pragma once

#include <QJsonObject>

namespace soda {

namespace pluginapi {

class AlgorithmNode {

public:
  virtual ~AlgorithmNode() {}
  virtual void setConfiguration(const QJsonObject) = 0;
  virtual void getConfiguration(QJsonObject &) const = 0;
  virtual void run() = 0;

  // Exceptions
  class InvalidConfiguration {};
};

} // namespace pluginapi

} // namespace soda
