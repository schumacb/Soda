#pragma once

#include <memory>
#include <string>

#include <QString>
#include <QUuid>
#include <QtPlugin>

QT_BEGIN_NAMESPACE
class QObject;
class QJsonObject;
QT_END_NAMESPACE

namespace soda {
class NodeType;
namespace pluginapi {

class Node {
public:
  virtual ~Node() = default;
  virtual const NodeType &getType() const = 0;

  virtual void setConfiguration(const QJsonObject &configuration) = 0;
  virtual const QJsonObject getConfiguration() const = 0;

  virtual const char *getSignal(int index) const = 0;
  virtual const char *getSlot(int index) const = 0;

  virtual void run() = 0;
};

class NodeFactory {
public:
  virtual ~NodeFactory() = default;
  virtual Node *createNode(QObject *parent = 0) const = 0;
  virtual const NodeType &getType() const = 0;
};

} // namespace pluginapi
} // namespace soda
