#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include <QTcpServer>
#include <map>
#include <QThread>
#include "ClientHandler.h"

class TcpServer : public QObject {
    Q_OBJECT

public:
    explicit TcpServer(QObject *parent = nullptr);
    bool startServer() noexcept;

signals:
    void clientConnected(int clientId);
    void clientDisconnected(int clientId);
    void messageReceived(int clientId, const QByteArray &message);

private slots:
    void onNewConnection();

private:
    int getNextClientId() noexcept;
    QTcpServer server;
    std::map<int, QThread*> clientThreads;
    int nextClientId{1};
};

#endif // TCPSERVER_HPP
