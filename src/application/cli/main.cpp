
#include <QCoreApplication>

#include <QDir>

#include "pluginmanager.hpp"

#include "utillity.hpp"

using namespace soda::plugin::utillity;

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
    FrameGrabber &fg = ut->getFrameGrabber();
    ImageRenderer &ir = ut->getImageRenderer();

    QObject::connect(&fg, SIGNAL(imageReady(cv::Mat)), &ir,
                     SLOT(process(cv::Mat)));

    while (true) {
      fg.run();
      cv::waitKey(20);
    }
  }

  // app.exec();

  return 0;
}
