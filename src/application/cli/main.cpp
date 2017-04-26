
#include <QCoreApplication>

#include <QDir>

#include "pluginmanager.hpp"

int main(int argc, char** argv) {

    QCoreApplication app(argc, argv);

    app.addLibraryPath(QCoreApplication::applicationDirPath()+"/../lib");
    PluginManager pm;
    pm.loadPlugins(app.libraryPaths());

    //app.exec();

    return 0;
}
