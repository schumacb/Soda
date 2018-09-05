#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char **argv) {

    auto app = new QApplication(argc, argv);


    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/AboutDialog.qml")));

    return app->exec();
}
