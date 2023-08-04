#ifndef DNSENTRY_H
#define DNSENTRY_H


#include "src/models/ipaddress.h"
#include <QString>

class DNSEntry
{
private:
    QString name;
    quint16 type;
    quint16 dnsClass;
    quint32 ttl;
    quint16 dataLength;
    IPAddress address;
public:
    DNSEntry(const QString &name, quint16 type, quint16 dnsClass, quint32 ttl = 0, quint16 dataLength = 0, const IPAddress &address = IPAddress());
    static DNSEntry fromString(const QString &str);
    QString getName() const;
    quint16 getType() const;
    quint16 getDnsClass() const;
    quint32 getTtl() const;
    quint16 getDataLength() const;
    IPAddress getAddress() const;
};

#endif // DNSENTRY_H
