#ifndef MAC_H
#define MAC_H

#include <QString>
#include "src/models/macaddress.h"
#include "src/models/package.h"

class MAC
{
public:
    static void initHeader(Package& data, const MACAddress &destMACAdress, const MACAddress &srcMACAdress, quint16 etherType);

private:
    static quint32 getFCS(const MACAddress &destMACAdress, const MACAddress &srcMACAdress, quint16 etherType, const Package &data);

    static quint32 calculateCRC32(const QByteArray &data);
};

#endif // MAC_H
