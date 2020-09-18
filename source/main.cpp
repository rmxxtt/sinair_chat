#include "mainwindow.h"
#include "sslclient.h"
#include "json.h"

#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    SslClient client(QUrl(QStringLiteral("wss://sinair.ru/ws/chat")));
    Q_UNUSED(client);

    return a.exec();
}
