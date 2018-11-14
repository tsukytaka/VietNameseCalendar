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
//    qCritical("HttpRequestHandler: you need to override the service() function");
    qDebug("HttpRequestHandler: request=%s %s %s %s",request.getMethod().data(),request.getPath().data(),request.getVersion().data());
//    response.setStatus(501,"not implemented");
//    response.write("501 not implemented",true);
    QString requestPath = QString::fromLatin1(request.getPath());
    qDebug() << "requestPath = " << requestPath;

    if (requestPath.compare(AUTHENTICATE_PATH) == 0) {
        //get authorization code
        QString authorization_code = request.getParameter(CODE_PARAMATER_TAG);
        qDebug() << "authorization_code = " << authorization_code;
        // redirect to exchange access_token
//        QString m_strEndPointToken = "https://accounts.google.com/o/oauth2/token";
//        QString m_strScope = "https://www.googleapis.com/auth/calendar";
//        QString m_strClientID = "760581500921-17vl6s2lsu2mi2qnscn1tqrbhsmvc5ga.apps.googleusercontent.com";
//        QString m_strClientSecret = "EXPax6A6wX745yNw7EKep9o3";
//        QString m_strRedirectURI = "https://localhost:8080/receive_token";
//        QString m_strResponseType = "token";
//        QString str = QString("%1").arg(m_strEndPointToken);
//        QString str = QString("%1?grant_type=authorization_code&code=%2&redirect_uri=%3&client_id=%4&client_secret=%5").arg(m_strEndPointToken).arg(authorization_code).arg(m_strRedirectURI).arg(m_strClientID).arg(m_strClientSecret);
//        qDebug() << "Exchange access_token URL: " << str;
//        response.setStatus(302,"Found");
//        response.setHeader("Location", str.toLatin1());
        response.write("Authenticate success",true);
    }


}
