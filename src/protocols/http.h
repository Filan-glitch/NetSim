#ifndef HTTP_H
#define HTTP_H

#include <QString>



class HTTP
{
public:
    static void initHTTPRequest(QString requestType, QString url, QString version);
    static void initHTTPResponse(QString version, qint16 messageCode, QString messageText);
};

#endif // HTTP_H
