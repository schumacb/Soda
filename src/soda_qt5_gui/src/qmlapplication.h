#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class QmlApplication : public QGuiApplication {
    Q_OBJECT
private:
    QQmlApplicationEngine m_qml_engine;
public:
    QmlApplication(int argc, char* argv[]);
    int virtual exec();
public slots:
    void load();
};
