
#include <QCoreApplication>

#include <QDir>

#include "pluginmanager.hpp"

int main(int argc, char** argv) {

    QCoreApplication app(argc, argv);

    app.addLibraryPath(QCoreApplication::applicationDirPath()+"/../../plugin/utillity");

    PluginManager pm;
    pm.loadPlugins(&app);

    //app.exec();

    return 0;
}
