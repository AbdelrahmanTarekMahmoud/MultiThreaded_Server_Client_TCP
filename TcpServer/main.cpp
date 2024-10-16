#include <QCoreApplication>
#include "TcpServer.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    TcpServer server;
    if (server.startServer()) {
        qDebug() << "Server is running...";
    }

    return a.exec();
}
