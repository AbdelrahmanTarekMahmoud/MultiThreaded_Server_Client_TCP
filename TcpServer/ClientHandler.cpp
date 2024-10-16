#include "ClientHandler.h"
#include <QDebug>
#include <QThread>

ClientHandler::ClientHandler(QTcpSocket *socket, int clientId, QObject *parent)
    : QObject(parent), clientSocket(socket), clientId(clientId) {
}


void ClientHandler::onReadyRead() {
    qDebug() << "Ready to read data from client in thread:" << QThread::currentThreadId();

    if (clientSocket->bytesAvailable() > 0) {
        QByteArray data = clientSocket->readAll();
        qDebug() << "Data received from client" << clientId << ":" << data;

        QByteArray processedData = "Processed: " + data;

        qDebug() << "Finished processing data in thread:" << QThread::currentThreadId();

        emit finishedProcessing(processedData);
    }
}

void ClientHandler::onDisconnected() {
    qDebug() << "Client" << clientId << "disconnected in thread:" << QThread::currentThreadId();
    clientSocket->deleteLater();
    emit finished();
}
