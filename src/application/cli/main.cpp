
#include <opencv2/opencv.hpp>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>

#include "applicationmodel.hpp"
#include "flowsceneparser.hpp"
#include "pluginmanager.hpp"
#include "server.hpp"

using namespace soda;
using namespace soda::pluginapi;
using namespace soda::network;

int main(int argc, char **argv) {

  QCoreApplication app(argc, argv);
  ApplicationModel model(&app);
  model.initialize();
  PluginManager &pm = *model.getPluginManager();
  Server server;
  QHostAddress adress = QHostAddress::Any;
  quint16 port = 0;
  if (server.listen(adress, port)) {
    qDebug() << "Server listening on: " << server.getAdress() << ":"
             << server.getPort();
  }

  if (argc == 3) {
    auto file_name = argv[1];
    auto start_node_id = QUuid(argv[2]);
    QFile f(file_name);
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
      qDebug() << "Can't read file \"" << file_name << "\"!";
      return -1;
    }
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    QJsonObject flowScene{doc.object()};
    FlowSceneParser parser(&pm);
    parser.parse(flowScene);

    Node *start_node = pm.getNode(start_node_id);

    while (true) {
      start_node->run();
      cv::waitKey(20);
      app.processEvents();
    }
  } else {
    qDebug() << "Usage: soda-cli <path-to-config.flow> <start-node-id> \n Use "
                "soda to create config.flow.";
    app.exec();
  }

  return 0;
}
