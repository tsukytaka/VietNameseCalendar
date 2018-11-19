#ifndef HTTPREQUESTHANDLER_H
#define HTTPREQUESTHANDLER_H

//#include "httpglobal.h"
#include "httprequest.h"
#include "httpresponse.h"

class HttpRequestHandler : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(HttpRequestHandler)
public:

    /**
     * Constructor.
     * @param parent Parent object.
     */
    HttpRequestHandler(QObject* parent=NULL);

    /** Destructor */
    ~HttpRequestHandler();

    /**
      Generate a response for an incoming HTTP request.
      @param request The received HTTP request
      @param response Must be used to return the response
      @warning This method must be thread safe
    */
    void service(HttpRequest& request, HttpResponse& response);

signals:
    void receivedAuthCode(QString authCode);

};

#endif // HTTPREQUESTHANDLER_H
