#include <QCoreApplication>
#include "TcpClient.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    TcpClient client;
    client.connectToServer();

    QObject::connect(&client, &TcpClient::connected, [&]() {
        client.sendMessage("Hello from client!");
    });

    return a.exec();
}
