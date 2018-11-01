#ifndef WEBLISTENERSERVER_H
#define WEBLISTENERSERVER_H

#include <QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <QtNetwork/QSslError>
#include <QWebSocketServer>
#include <QWebSocket>

#define CERT_FILE_NAME "./cert.pem"
#define KEY_FILE_NAME "./key.pem"

class WebListenerServer : public QObject
{
    Q_OBJECT
public:
    explicit WebListenerServer(quint16 port, QObject *parent = 0);
    virtual ~WebListenerServer();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void onSslErrors(const QList<QSslError> &errors);

signals:

public slots:

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
};

#endif // WEBLISTENERSERVER_H
