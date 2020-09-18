#ifndef SSLCLIENT_H
#define SSLCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QUrl>

QT_FORWARD_DECLARE_CLASS(QWebSocket)

class SslClient : public QObject
{
    Q_OBJECT
public:
    explicit SslClient(const QUrl &url, QObject *parent = nullptr);
    void sendMessage(QString message);

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onSslErrors(const QList<QSslError> &errors);

private:
    QWebSocket m_webSocket;
};

#endif // SSLCLIENT_H
