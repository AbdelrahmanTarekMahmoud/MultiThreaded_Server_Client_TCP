#include "TcpClient.h"
#include <QDebug>
#include <string_view>

constexpr std::string_view SERVER_IP = "127.0.0.1";
constexpr int SERVER_PORT = 12345;

TcpClient::TcpClient(QObject *parent)
    : QObject(parent), tcpSocket(new QTcpSocket(this)) {
    connect(tcpSocket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
}

void TcpClient::connectToServer() {
    if (tcpSocket->state() == QAbstractSocket::UnconnectedState) {
        tcpSocket->connectToHost(QString::fromUtf8(SERVER_IP.data()), SERVER_PORT);
    }
}

void TcpClient::sendMessage(const QByteArray &message) {
    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        tcpSocket->write(message);
    } else {
        qWarning() << "Not connected to the server.";
    }
}

void TcpClient::onConnected() {
    qDebug() << "Connected to server.";
    emit connected();
}

void TcpClient::onReadyRead() {
    QByteArray message = tcpSocket->readAll();
    emit messageReceived(message);
    qDebug() << "Message received from server:" << message;
}
