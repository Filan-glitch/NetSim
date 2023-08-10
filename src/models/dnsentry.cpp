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

QVector<quint8> DNSEntry::getData() const
{
    return data;
}

DNSEntry::DNSEntry(const QString &name, quint16 type, quint16 dnsClass, quint32 ttl, const QVector<quint8> &data) : name(name),
    type(std::move(type)),
    dnsClass(std::move(dnsClass)),
    ttl(std::move(ttl)),
    dataLength(data.size()),
    data(data)
{}
