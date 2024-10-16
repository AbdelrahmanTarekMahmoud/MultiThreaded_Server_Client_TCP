#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include <QTcpSocket>

class ClientHandler : public QObject {
    Q_OBJECT

public:
    ClientHandler(QTcpSocket *socket, int clientId, QObject *parent = nullptr);

public slots:
    void onReadyRead();
    void onDisconnected();

signals:
    void finished();
    void finishedProcessing(const QByteArray &data);

private:
    QTcpSocket *clientSocket;
    int clientId;
};

#endif // CLIENTHANDLER_H
