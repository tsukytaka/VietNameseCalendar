#ifndef HTTPCONNECTIONHANDLERPOOL_H
#define HTTPCONNECTIONHANDLERPOOL_H

#include <QList>
#include <QTimer>
#include <QObject>
#include <QMutex>
//#include "httpglobal.h"
#include "httpconnectionhandler.h"

class HttpConnectionHandlerPool : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(HttpConnectionHandlerPool)
public:

    /**
      Constructor.
      @param settings Configuration settings for the HTTP server. Must not be 0.
      @param requestHandler The handler that will process each received HTTP request.
      @warning The requestMapper gets deleted by the destructor of this pool
    */
    HttpConnectionHandlerPool(QSettings* settings, HttpRequestHandler* requestHandler);

    /** Destructor */
    virtual ~HttpConnectionHandlerPool();

    /** Get a free connection handler, or 0 if not available. */
    HttpConnectionHandler* getConnectionHandler();

private:

    /** Settings for this pool */
    QSettings* settings;

    /** Will be assigned to each Connectionhandler during their creation */
    HttpRequestHandler* requestHandler;

    /** Pool of connection handlers */
    QList<HttpConnectionHandler*> pool;

    /** Timer to clean-up unused connection handler */
    QTimer cleanupTimer;

    /** Used to synchronize threads */
    QMutex mutex;

    /** The SSL configuration (certificate, key and other settings) */
    QSslConfiguration* sslConfiguration;

    /** Load SSL configuration */
    void loadSslConfig();

private slots:

    /** Received from the clean-up timer.  */
    void cleanup();

};

#endif // HTTPCONNECTIONHANDLERPOOL_H
