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
     * @param data
     * @par adds the HTTP-Request Header to a package
     */
    static void initHTTPRequest(const QString &requestType, const QString &url, const QString &version, Package& data);
  
    /**
     * @brief initHTTPResponse
     * @param version
     * @param messageCode
     * @param messageText
     * @param data
     * @par adds the HTTP-Response Header to a package
     */
    static void initHTTPResponse(const QString &version, qint16 messageCode, const QString &messageText, Package& data);
};

#endif // HTTP_H
