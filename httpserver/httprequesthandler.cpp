#include "httprequesthandler.h"
#define AUTHENTICATE_PATH "/authenticate"
#define CODE_PARAMATER_TAG "code"

HttpRequestHandler::HttpRequestHandler(QObject* parent)
    : QObject(parent)
{}

HttpRequestHandler::~HttpRequestHandler()
{}

void HttpRequestHandler::service(HttpRequest& request, HttpResponse& response)
{
    QString requestPath = QString::fromLatin1(request.getPath());
    qDebug() << "requestPath = " << requestPath;

    if (requestPath.compare(AUTHENTICATE_PATH) == 0) {
        //get authorization code
        QString authorization_code = request.getParameter(CODE_PARAMATER_TAG);
        qDebug() << "authorization_code = " << authorization_code;
        response.write("Authenticate success",true);

        emit receivedAuthCode(authorization_code);
    }
    else
    {
        response.setStatus(501,"not implemented");
        response.write("501 not implemented",true);
    }


}
