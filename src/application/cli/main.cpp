
#include <QCoreApplication>

#include <QDir>

#include "pluginmanager.hpp"

#include "utillity.hpp"

using namespace soda::plugin::utillity;
using namespace soda::pluginapi;

int main(int argc, char **argv) {

  QCoreApplication app(argc, argv);

  app.addLibraryPath(QCoreApplication::applicationDirPath() + "/../lib");
  PluginManager pm;

  auto libPaths = app.libraryPaths();

  pm.loadPlugins(libPaths);

  Plugin *pi = pm.findPlugin("de.hochschule-trier.soda.plugin.utillity",
                             Version{0, 1, 0});
  if (pi) {
    Utillity *ut = dynamic_cast<Utillity *>(pi);
    // Utillity* ut = (Utillity*)pi;
    QObject *iso = dynamic_cast<QObject *>(&ut->getFrameGrabber());
    QObject *ipo = dynamic_cast<QObject *>(&ut->getImageRenderer());
    ImageSource *is = &ut->getFrameGrabber();

    QObject::connect(iso, SIGNAL(signal_imageReady(cv::Mat)), ipo,
                     SLOT(slot_process(cv::Mat)));

    while (true) {
      is->run();
      cv::waitKey(20);
    }
  }

  // app.exec();

  return 0;
}
