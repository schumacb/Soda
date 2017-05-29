
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

  if (argc == 2) {
    auto file_name = argv[1];
    QFile f(file_name);
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
      qDebug() << "Can't read file \"" << file_name << "\"!";
      return -1;
    }
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    QJsonObject flowScene{doc.object()};
    FlowSceneParser parser(&pm);
    parser.parse(flowScene);

    // TODO: parse connection
    AlgorithmNode *fg =
        pm.getNode(QUuid("{a64a093c-5128-481f-abf0-5652244e9c69}"));
    AlgorithmNode *ip =
        pm.getNode(QUuid("{610d6ff3-d403-4773-9f23-b26e5790e559}"));
    QObject *fgo = dynamic_cast<QObject *>(fg);
    QObject *ipo = dynamic_cast<QObject *>(ip);
    QObject::connect(fgo, SIGNAL(signal_imageReady(cv::Mat)), ipo,
                     SLOT(slot_process(cv::Mat)));
    // TODO: end

    while (true) {
      fg->run();
      cv::waitKey(20);
    }
  }

  // app.exec();

  return 0;
}
