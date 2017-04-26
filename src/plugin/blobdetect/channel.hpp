#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Channel : public QObject
{
    Q_OBJECT
public:
    explicit Channel(QObject *parent = 0);

signals:

public slots:
};

#endif // CHANNEL_HPP
