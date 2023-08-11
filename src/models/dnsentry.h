#ifndef DNSENTRY_H
#define DNSENTRY_H

#include "src/models/ipaddress.h"
#include <QString>

namespace NetSim {
enum RRAttribute { FULL_DATA, NAME, TYPE, CLASS, TTL, DATA_LENGTH, DATA };
class DNSEntry;
} // namespace NetSim

class DNSEntry {
public:
  DNSEntry(const QString &name, quint16 type, quint16 dnsClass, quint32 ttl = 0,
           const QVector<quint8> &data = QVector<quint8>());

  QString name() const;

  quint16 type() const;

  quint16 dnsClass() const;

  quint32 ttl() const;

  quint16 dataLength() const;

  QVector<quint8> data() const;

private:
  QString m_name;

  quint16 m_type;

  quint16 m_class;

  quint32 m_ttl;

  QVector<quint8> m_data;
};

#endif // DNSENTRY_H
