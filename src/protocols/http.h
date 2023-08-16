#ifndef HTTP_H
#define HTTP_H

#include "src/models/package.h"
#include <QString>

//! \file http.h
//! \ingroup NetSimHTTP
//! \brief Contains the HTTP class definition.

namespace NetSim {

//! \defgroup NetSimHTTP HTTP
//! \brief Provides functionalities to handle HTTP requests and responses.

/**
 * @class HTTP
 * @ingroup NetSimHTTP
 * @brief A static class that provides methods to handle HTTP requests and
 * responses.
 *
 * The HTTP class contains static methods that can initialize HTTP request and
 * response headers. These methods can be utilized to easily create and
 * manipulate HTTP-related data within packages.
 */
class HTTP {
public:
  /**
   * @brief Initializes an HTTP request header.
   *
   * @param requestType The type of HTTP request (e.g., GET, POST).
   * @param uri The URI being requested.
   * @param version The HTTP version (e.g., HTTP/1.1).
   * @param data Reference to the package where the header should be added.
   */
  static void initHTTPRequest(const QString &requestType, const QString &uri,
                              const QString &version, Package &data);

  /**
   * @brief Initializes an HTTP response header.
   *
   * @param version The HTTP version (e.g., HTTP/1.1).
   * @param messageCode The HTTP status code (e.g., 200 for OK).
   * @param messageText The HTTP status message (e.g., "OK").
   * @param data Reference to the package where the header should be added.
   * @param htmlFile The content of the HTML response.
   */
  static void initHTTPResponse(const QString &version, quint16 messageCode,
                               const QString &messageText, Package &data,
                               const QString &htmlFile);
};
} // namespace NetSim

#endif // HTTP_H
