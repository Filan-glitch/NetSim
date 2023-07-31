#ifndef IPV4_H
#define IPV4_H

#include <QString>
#include <QList>
#include <QDebug>
#include "src/models/ipaddress.h"
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
    static void initHeader(quint16 id, bool DF, bool MF, quint16 fragmentOffset, quint8 ttl, quint8 protocol, const IPAddress &sourceAddress, const IPAddress &destinationAdress, Package& data);

    static QList<Package> fragmentPackage(const Package& package, quint32 mtu);
private:
    static quint16 getIPv4Checksum(quint16 totalLength, quint16 id, quint8 flags, quint16 fragOffset, quint8 ttl, quint8 protocol, quint8* srcAddress, quint8* destAddress, const char* data, quint16 dataLength);
    static void setFlag(quint8* flags, bool set, quint8 position);
};

#endif // IPV4_H
