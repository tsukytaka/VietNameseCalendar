#ifndef HTTPLISTENER_H
#define HTTPLISTENER_H
#include <QTcpServer>
#include <QSettings>

class HttpListener : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(HttpListener)
public:
    HttpListener(QSettings* settings, QObject* parent = NULL);

    virtual ~HttpListener();

    void listen();
    void close();


protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    QSettings* settings;

//    /** Point to the reuqest handler which processes all HTTP requests */
//    HttpRequestHandler* requestHandler;

//    /** Pool of connection handlers */
//    HttpConnectionHandlerPool* pool;

signals:

//    /**
//      Sent to the connection handler to process a new incoming connection.
//      @param socketDescriptor references the accepted connection.
//    */

//    void handleConnection(tSocketDescriptor socketDescriptor);
};

#endif // HTTPLISTENER_H
