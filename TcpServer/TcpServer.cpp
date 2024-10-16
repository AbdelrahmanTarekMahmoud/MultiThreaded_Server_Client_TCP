#include "TcpServer.h"
#include <QDebug>

constexpr int SERVER_PORT = 12345;

TcpServer::TcpServer(QObject *parent) : QObject(parent) {
    connect(&server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
}

bool TcpServer::startServer() noexcept {
    if (!server.listen(QHostAddress::Any, SERVER_PORT)) {
        qCritical() << "Server could not start!";
        return false;
    }
    qDebug() << "Server started on port 12345";
    return true;
}

int TcpServer::getNextClientId() noexcept {
    return nextClientId++;
}

void TcpServer::onNewConnection() {
    QTcpSocket *clientSocket = server.nextPendingConnection();
    int clientId = getNextClientId();

    qDebug() << "New client connected with ID:" << clientId;

    QThread *processingThread = new QThread(this);

    ClientHandler *handler = new ClientHandler(clientSocket, clientId);
    handler->moveToThread(processingThread);

    connect(clientSocket, &QTcpSocket::readyRead, handler, &ClientHandler::onReadyRead);
    connect(handler, &ClientHandler::finishedProcessing, this, [clientSocket](const QByteArray &processedData) {

        clientSocket->write(processedData);
    });

    connect(clientSocket, &QTcpSocket::disconnected, handler, &ClientHandler::onDisconnected);
    connect(handler, &ClientHandler::finished, processingThread, &QThread::quit);
    connect(handler, &ClientHandler::finished, handler, &ClientHandler::deleteLater);
    connect(processingThread, &QThread::finished, processingThread, &QThread::deleteLater);

    processingThread->start();

    emit clientConnected(clientId);
}
