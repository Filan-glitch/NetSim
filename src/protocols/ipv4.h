#ifndef IPV4_H
#define IPV4_H

#include <QString>
#include <QList>
#include "src/models/ipaddress.cpp"
#include "src/models/package.h"

/**
 * @brief The IPv4 class
 * @par This class represents the IPv4 Protocol
 */
class IPv4
{
public:
    /**
     * @brief initHeader
     * @param id
     * @param flags
     * @param fragmentOffset
     * @param ttl
     * @param protocol
     * @param sourceAdress
     * @param destinationAdress
     * @param options
     * @param data
     * @param dataLength
     * @par adds a IPv4 Header to a package
     */
    static void initHeader(qint16 id, bool DF, bool MF, qint16 fragmentOffset, qint8 ttl, qint8 protocol, const IPAddress &sourceAddress, const IPAddress &destinationAdress, Package& data);

    static QList<Package> fragmentPackage(const Package& package, qint32 mtu);
private:
    static qint16 getIPv4Checksum(qint16 totalLength, qint16 id, qint8 flags, qint16 fragOffset, qint8 ttl, qint8 protocol, qint8* srcAddress, qint8* destAddress, const char* data, qint16 dataLength);
    static void setFlag(qint8* flags, bool set, qint8 position);
};

#endif // IPV4_H
