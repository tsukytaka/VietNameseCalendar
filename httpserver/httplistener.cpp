#include "httplistener.h"

HttpListener::HttpListener(QSettings* settings, HttpRequestHandler* requestHandler, QObject *parent): QTcpServer(parent)
{
    Q_ASSERT(settings!=0);
    Q_ASSERT(requestHandler!=0);
    pool=NULL;
    this->settings=settings;
    this->requestHandler=requestHandler;
    // Reqister type of socketDescriptor for signal/slot handling
    qRegisterMetaType<qintptr>("qintptr");
    // Start listening
    listen();
}

HttpListener::~HttpListener()
{
    close();
//    delete settings;
    delete requestHandler;
    if (pool)
    {
        delete pool;
    }
    qDebug("HttpListener: destroyed");
}


void HttpListener::listen()
{
    if (!pool)
    {
        pool=new HttpConnectionHandlerPool(settings, requestHandler);
    }
    QString host = settings->value("host").toString();
    int port = settings->value("port", 80).toInt();
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

    HttpConnectionHandler* freeHandler=NULL;
    if (pool)
    {
        freeHandler=pool->getConnectionHandler();
    }

    // Let the handler process the new connection.
    if (freeHandler)
    {
        // The descriptor is passed via event queue because the handler lives in another thread
        QMetaObject::invokeMethod(freeHandler, "handleConnection", Qt::QueuedConnection, Q_ARG(qintptr, socketDescriptor));
    }
    else
    {
        // Reject the connection
        qDebug("HttpListener: Too many incoming connections");
        QTcpSocket* socket=new QTcpSocket(this);
        socket->setSocketDescriptor(socketDescriptor);
        connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
        socket->write("HTTP/1.1 503 too many connections\r\nConnection: close\r\n\r\nToo many connections\r\n");
        socket->disconnectFromHost();
    }
}
