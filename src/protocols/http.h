#ifndef HTTP_H
#define HTTP_H

#include <QString>
#include "src/models/package.h"

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
    static void initHTTPRequest(const QString &requestType, const QString &url, const QString &version, Package& data);
  
    /**
     * @brief initHTTPResponse
     * @param version
     * @param messageCode
     * @param messageText
     * @par adds the HTTP-Response Header to a package
     */
    static void initHTTPResponse(const QString &version, qint16 messageCode, const QString &messageText);
};

#endif // HTTP_H
