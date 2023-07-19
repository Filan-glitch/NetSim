#ifndef HTTP_H
#define HTTP_H

#include <QString>

/**
 * @brief The HTTP class
 * @par represents the HTTP Protocoll
 */

class HTTP
{
public:
    /**
     * @brief initHTTPRequest
     * @param requestType
     * @param url
     * @param version
     * @par adds the HTTP-Request Header to a package
     */
    static void initHTTPRequest(QString requestType, QString url, QString version);
  
    /**
     * @brief initHTTPResponse
     * @param version
     * @param messageCode
     * @param messageText
     * @par adds the HTTP-Response Header to a package
     */
    static void initHTTPResponse(QString version, qint16 messageCode, QString messageText);
};

#endif // HTTP_H
