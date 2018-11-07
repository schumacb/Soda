#include <QApplication>

#include <mainwindow.h>

using namespace soda;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow mainWindow(nullptr);
    app.quitOnLastWindowClosed();
    mainWindow.show();
    return app.exec();
}
