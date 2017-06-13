#pragma once

#include <QTcpSocket>
#include <QUdpSocket>
#include <QUuid>
#include <QtCore/qglobal.h>

namespace soda {
namespace network {

class Client : public QTcpSocket {

  QUuid uuid{QUuid::createUuid()};

public:
  Client();
};

} // namespace network
} // namespace soda
