#ifndef IPV4_H
#define IPV4_H

#include <QString>
#include <QList>
#include <QDebug>
#include <QVector>
#include "src/models/ipaddress.h"
#include "src/models/package.h"

enum IPFlag
{
    MF = 0,
    DF = 1
};

class IPv4
{
public:
    static void initHeader(quint16 id, bool DF, bool MF, quint16 fragmentOffset, quint8 ttl, quint8 protocol, const IPAddress &sourceAddress, const IPAddress &destinationAdress, Package& data);

private:
    static quint16 getIPv4Checksum(quint16 totalLength, quint16 id, quint8 flags, quint16 fragOffset, quint8 ttl, quint8 protocol, const QVector<quint8> &srcAddress, const QVector<quint8> &destAddress, const char* data, quint16 dataLength);

    static void setFlag(quint8 *flags, bool set, quint8 position);
};

#endif // IPV4_H
