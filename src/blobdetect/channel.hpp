#pragma once

#include <QObject>
#include <qglobal.h>

class Channel : public QObject {
  Q_OBJECT
public:
  explicit Channel(QObject *parent = 0);

signals:

public slots:
};
