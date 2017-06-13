#pragma once

#include <QHostAddress>
#include <QObject>

QT_BEGIN_NAMESPACE
class QTcpServer;
class QTcpSocket;
class QUdpSocket;
QT_END_NAMESPACE

namespace soda {
namespace network {

class Connection : public QObject {
  Q_OBJECT

  QTcpSocket *m_socket;

  enum class ConnectionState { WaitForGreeting, Ready, Error };
  enum class ConnectionType { JSonUTF8, JSonBinary };
  ConnectionState m_state{ConnectionState::WaitForGreeting};

public:
  Connection(QTcpSocket *socket, QObject *parent = 0);
  Connection(const Connection &other) = delete;
  const Connection &operator=(const Connection &other) = delete;

public slots:
  void on_socket_readyRead();
};

class Server : public QObject {
  Q_OBJECT

private:
  QList<QHostAddress> m_broadcast_adresses{};
  QList<QHostAddress> m_ip_adresses{};

  QTcpServer *m_server;
  QUdpSocket *m_broadcast_socket;

  void updateAdresses();

public:
  explicit Server(QObject *parent = 0);

  Server(const Server &other) = delete;
  const Server &operator=(const Server &other) = delete;

  QHostAddress getAdress();
  quint16 getPort();

  bool listen(QHostAddress &adress, quint16 port);

signals:
  void newConnection(Connection *connection);

public slots:
  void on_server_newConnection();
};

} // namespace network
} // namespace soda
