#include "server.hpp"

#include <QHostAddress>
#include <QNetworkInterface>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

using namespace soda::network;

Server::Server(QObject *t_parent)
    : QObject(t_parent), m_server{new QTcpServer(this)},
      m_broadcast_socket{new QUdpSocket(this)} {
  connect(m_server, SIGNAL(newConnection()), this,
          SLOT(on_server_newConnection()));
}
void Server::updateAdresses() {
  m_broadcast_adresses.clear();
  m_ip_adresses.clear();
  for (auto interface : QNetworkInterface::allInterfaces()) {
    for (auto entry : interface.addressEntries()) {
      auto broadcast_adress = entry.broadcast();
      if (broadcast_adress != QHostAddress::Null &&
          entry.ip() != QHostAddress::LocalHost) {
        m_broadcast_adresses << broadcast_adress;
        m_ip_adresses << entry.ip();
      }
    }
  }
}

QHostAddress Server::getAdress() { return m_server->serverAddress(); }

quint16 Server::getPort() { return m_server->serverPort(); }

bool Server::listen(QHostAddress &t_adress, quint16 t_port) {
  return m_server->listen(t_adress, t_port);
}

void Server::on_server_newConnection() {
  auto *connection = new Connection(m_server->nextPendingConnection(), this);
}

Connection::Connection(QTcpSocket *t_socket, QObject *t_parent)
    : QObject(t_parent), m_socket{t_socket} {
  connect(m_socket, SIGNAL(readyRead()), this, SLOT(on_socket_readyRead()));
  connect(m_socket, SIGNAL(disconnected()), this,
          SLOT(on_socket_disconnected()));
}

void Connection::on_socket_readyRead() {
  qDebug() << "TcpServer:readyRead" << m_socket->readAll();

  switch (m_state) {
  case ConnectionState::WaitForGreeting:
    // TODO: Check Version
    break;
  case ConnectionState::Ready:
    break;
  case ConnectionState::Error:
    break;
  }
}
