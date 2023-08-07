#ifndef DNSENTRY_H
#define DNSENTRY_H


#include "src/models/ipaddress.h"
#include <QString>

enum RRAttribute {
    FULL_DATA,
    NAME,
    TYPE,
    CLASS,
    TTL,
    DATA_LENGTH,
    DATA
};

class DNSEntry
{
private:
    QString name;
    quint16 type;
    quint16 dnsClass;
    quint32 ttl;
    quint16 dataLength;
    QVector<quint8> data;
public:
    DNSEntry(const QString &name, quint16 type, quint16 dnsClass, quint32 ttl = 0, quint16 dataLength = 0, const QVector<quint8> &data = QVector<quint8>());
    QString getName() const;
    quint16 getType() const;
    quint16 getDnsClass() const;
    quint32 getTtl() const;
    quint16 getDataLength() const;
    QVector<quint8> getData() const;

};

#endif // DNSENTRY_H
