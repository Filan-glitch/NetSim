#include "dnsentry.h"

QString DNSEntry::getName() const
{
    return name;
}

quint16 DNSEntry::getType() const
{
    return type;
}

quint16 DNSEntry::getDnsClass() const
{
    return dnsClass;
}

quint32 DNSEntry::getTtl() const
{
    return ttl;
}

quint16 DNSEntry::getDataLength() const
{
    return dataLength;
}

IPAddress DNSEntry::getAddress() const
{
    return address;
}

DNSEntry::DNSEntry(const QString &name, quint16 type, quint16 dnsClass, quint32 ttl, quint16 dataLength, const IPAddress &address) : name(name),
    type(std::move(type)),
    dnsClass(std::move(dnsClass)),
    ttl(std::move(ttl)),
    dataLength(std::move(dataLength)),
    address(address)
{}

DNSEntry DNSEntry::fromString(const QString& str)
{
    QString name;
    quint16 type = 0;
    quint16 dnsClass = 0;
    quint32 ttl = 0;
    quint16 dataLength = 0;
    IPAddress address;

    return DNSEntry(name, type, dnsClass, ttl, dataLength, address);
}
