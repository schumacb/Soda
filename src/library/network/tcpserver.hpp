#pragma once

#include <QObject>
#include <QTcpServer>

namespace soda {
namespace network {

class TcpServer : public QTcpServer {
public:
  TcpServer();

signals:

public slots:
};

} // namespace network
} // namespace soda
