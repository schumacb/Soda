#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char **argv) {

    auto app = new QGuiApplication(argc, argv);

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/AboutDialog.qml")));

    return app->exec();
}
