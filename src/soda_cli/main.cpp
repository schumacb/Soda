#include <QCoreApplication>

#include <opencv2/highgui.hpp>

#include "framegrabber.hpp"

using namespace soda;

int main(int argc, char **argv) {

    QCoreApplication app(argc, argv);

    app.addLibraryPath(QCoreApplication::applicationDirPath() + "/../lib");

    auto framegrabber = new FrameGrabber(0);
    framegrabber->open(0);

    app.exec();
    return 0;
}
