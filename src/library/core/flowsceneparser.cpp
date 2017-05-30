#include "flowsceneparser.hpp"

#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QUuid>

#include <QDebug>

#include "algorithm.hpp"
#include "pluginmanager.hpp"

namespace soda {

using namespace pluginapi;

FlowSceneParser::FlowSceneParser(PluginManager *t_plugin_manager)
    : m_plugin_manager{t_plugin_manager} {}

void FlowSceneParser::parse(const QJsonObject &t_json) {

  QJsonArray connections = t_json["connections"].toArray();

  QJsonArray nodes = t_json["nodes"].toArray();

  for (int nodeIndex = 0; nodeIndex < nodes.size(); ++nodeIndex) {

    QJsonObject nodeObject = nodes[nodeIndex].toObject();
    QUuid uuid{nodeObject["id"].toString()};
    QJsonObject nodeModel = nodeObject["model"].toObject();
    QString name = nodeModel["name"].toString();
    QString pid = nodeModel["pid"].toString();
    qDebug() << "Found node " << name << " of type " << pid
             << " with UUID: " << uuid.toString();
    AlgorithmNode *node = m_plugin_manager->getNode(uuid);
    if (node == nullptr) {
      node = m_plugin_manager->createNode(uuid, pid);
    }

    if (node != nullptr) {
      node->setConfiguration(nodeModel);
    }
  }

  for (int i = 0; i < connections.size(); ++i) {
    QJsonObject connectionObjcet = connections[i].toObject();
    QUuid in_id{connectionObjcet["in_id"].toString()};
    QUuid out_id{connectionObjcet["out_id"].toString()};
    int in_index{connectionObjcet["in_index"].toInt()};
    int out_index{connectionObjcet["out_index"].toInt()};
    AlgorithmNode *in_node = m_plugin_manager->getNode(in_id);
    AlgorithmNode *out_node = m_plugin_manager->getNode(out_id);
    if (in_node != nullptr && out_node != nullptr) {
      QObject *sender = dynamic_cast<QObject *>(out_node);
      QObject *receiver = dynamic_cast<QObject *>(in_node);
      const char *signal = out_node->getSignal(out_index);
      const char *slot = in_node->getSlot(in_index);
      QObject::connect(sender, signal, receiver, slot);
    }
  }
}

} // namespace soda
