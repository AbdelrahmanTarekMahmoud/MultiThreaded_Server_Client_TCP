#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <QTcpSocket>

class TcpClient : public QObject {
    Q_OBJECT

public:
    explicit TcpClient(QObject *parent = nullptr);
    void connectToServer();
    void sendMessage(const QByteArray &message);

signals:
    void connected();
    void messageReceived(const QByteArray &message);

private slots:
    void onConnected();
    void onReadyRead();

private:
    QTcpSocket *tcpSocket;
};

#endif // TCPCLIENT_HPP
