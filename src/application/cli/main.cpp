
#include <QCoreApplication>

#include <QDir>

#include "applicationmodel.hpp"
#include "flowsceneparser.hpp"
#include "framegrabber.hpp"
#include "imagesender.hpp"
#include "pluginmanager.hpp"

using namespace soda;
using namespace soda::pluginapi;
using namespace soda::plugin::framegrabber;
using namespace soda::plugin::imagesender;

int main(int argc, char **argv) {

  QCoreApplication app(argc, argv);
  ApplicationModel model(&app);
  model.initialize();
  PluginManager &pm = *model.pluginManager();

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

    AlgorithmNode *fg = pm.getNode(start_node_id);

    while (true) {
      fg->run();
      cv::waitKey(20);
    }
  } else {
    qDebug() << "Usage: soda-cli <path-to-config.flow> <start-node-id> \n Use "
                "soda to create config.flow.";
  }

  return 0;
}
