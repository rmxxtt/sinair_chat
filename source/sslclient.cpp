#include "sslclient.h"
#include <QtCore/QDebug>
#include <QtWebSockets/QWebSocket>
#include <QCoreApplication>

QT_USE_NAMESPACE

SslClient::SslClient(const QUrl &url, QObject *parent) :
    QObject(parent)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &SslClient::onConnected);
    connect(&m_webSocket, QOverload<const QList<QSslError>&>::of(&QWebSocket::sslErrors),
            this, &SslClient::onSslErrors);
    m_webSocket.open(QUrl(url));
}

void SslClient::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &SslClient::onTextMessageReceived);
    m_webSocket.sendTextMessage(QStringLiteral("{\"type\":6,\"target\":\"#qtbot\",\"auto_login\":true,\"load_history\":false}"));
    m_webSocket.sendTextMessage(QStringLiteral("{\"type\":2,\"target\":\"#qtbot\",\"message\":\"/nick qtcpp\",\"time\":0}"));
    m_webSocket.sendTextMessage(QStringLiteral("{\"type\":2,\"target\":\"#qtbot\",\"message\":\"Hello\",\"time\":0}"));
}

void SslClient::onTextMessageReceived(QString message)
{
    qDebug() << "Message received:" << message;
    //qApp->quit();
}

void SslClient::onSslErrors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors);

    // WARNING: Never ignore SSL errors in production code.
    // The proper way to handle self-signed certificates is to add a custom root
    // to the CA store.

    m_webSocket.ignoreSslErrors();
}

void SslClient::sendMessage(QString message)
{
    qDebug() << message;
}
