#include "flowsceneparser.hpp"

#include <QJsonArray>
#include <QJsonObject>
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
}

} // namespace soda
