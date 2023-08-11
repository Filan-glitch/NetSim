#ifndef DNS_H
#define DNS_H

#include "src/models/dnsentry.h"
#include "src/models/package.h"

namespace NetSim {
enum DNSFlag {
  REPLY_CODE = 0,
  NON_AUTHENTICATED_DATA = 4,
  ANSWER_AUTHENTICATED = 5,
  RECURSION_AVAILABLE = 7,
  RECURSION_DESIRED = 8,
  TRUNCATED = 9,
  AUTHORITATIVE = 10,
  OPCODE = 11,
  RESPONSE = 15
};
class DNS;
} // namespace NetSim

class DNS {
public:
  static void initDNSRequest(Package &data, const QList<DNSEntry> queries);

  static void initDNSResponse(Package &data, const QList<DNSEntry> queries,
                              const QList<DNSEntry> answers, bool nxDomain);

private:
  static void setFlag(quint16 *flags, bool set, quint8 position);

  static QVector<quint8> stringToArray(const QString &string);
};

#endif // DNS_H
