#include <QQuickStyle>
#include <QSettings>
#include "qmlapplication.h"

QmlApplication::QmlApplication(int argc, char* argv[])
    : QGuiApplication(argc, argv)
{
    QQmlContext *context = m_qml_engine.rootContext();
    context->setContextProperty("application", this);
    context->setContextProperty("availableStyles", QQuickStyle::availableStyles());
    QGuiApplication::setApplicationName(QStringLiteral("Soda"));
    QGuiApplication::setOrganizationName(QStringLiteral("Hochschule Trier - University of Applied Sciences Trier"));
    QSettings settings;
    QString style = QQuickStyle::name();
    if (!style.isEmpty())
    {
        settings.setValue("style", style);
    }
    else
    {
        style = settings.value("style").toString();
        qDebug(style.toStdString().c_str());
        QQuickStyle::setStyle(style);
    }
    load();
}

void QmlApplication::load()
{
//    QUrl(QStringLiteral("qrc:/MainWindow.qml"))
    m_qml_engine.clearComponentCache();
    m_qml_engine.load(QStringLiteral("C:/Users/Bastian Schumacher/workspace/Soda/src/soda_qt5_gui/forms/MainWindow.qml"));
}

int QmlApplication::exec() {
    if (m_qml_engine.rootObjects().isEmpty())
        return -1;
    return QGuiApplication::exec();
}
