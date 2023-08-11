#ifndef HTTP_H
#define HTTP_H

#include "src/models/package.h"
#include <QString>

namespace NetSim {
class HTTP;
}

class HTTP {
public:
  static void initHTTPRequest(const QString &requestType, const QString &uri,
                              const QString &version, Package &data);

  static void initHTTPResponse(const QString &version, quint16 messageCode,
                               const QString &messageText, Package &data,
                               const QString &htmlFile);
};

#endif // HTTP_H
