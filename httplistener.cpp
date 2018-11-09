#include "httplistener.h"

HttpListener::HttpListener(QSettings* settings, QObject *parent): QTcpServer(parent)
{
    Q_ASSERT(settings!=0);
    this->settings=settings;

    listen();
}

HttpListener::~HttpListener()
{
    close();
    qDebug("HttpListener: destroyed");
}


void HttpListener::listen()
{
    QString host = settings->value("host").toString();
    int port=settings->value("port").toInt();
    QTcpServer::listen(host.isEmpty() ? QHostAddress::Any : QHostAddress(host), port);
    if (!isListening())
    {
        qCritical("HttpListener: Cannot bind on port %i: %s",port,qPrintable(errorString()));
    }
    else {
        qDebug("HttpListener: Listening on port %i",port);
    }
}


void HttpListener::close() {
    QTcpServer::close();
    qDebug("HttpListener: closed");
}

void HttpListener::incomingConnection(qintptr socketDescriptor) {
    Q_ARG(qintptr, socketDescriptor);
//    // Let the handler process the new connection.
//    if (freeHandler)
//    {
//        // The descriptor is passed via event queue because the handler lives in another thread
//        QMetaObject::invokeMethod(freeHandler, "handleConnection", Qt::QueuedConnection, );
//    }
//    else
//    {
//        // Reject the connection
//        qDebug("HttpListener: Too many incoming connections");
//        QTcpSocket* socket=new QTcpSocket(this);
//        socket->setSocketDescriptor(socketDescriptor);
//        connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
//        socket->write("HTTP/1.1 503 too many connections\r\nConnection: close\r\n\r\nToo many connections\r\n");
//        socket->disconnectFromHost();
//    }
}
