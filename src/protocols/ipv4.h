#ifndef IPV4_H
#define IPV4_H

#include <QString>

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
     * @par adds a IPv4 Header to a package
     */
    static void initHeader(qint16 id, qint8 flags, qint16 fragmentOffset, qint8 ttl, qint8 protocol, qint32 sourceAdress, qint32 destinationAdress, char* options, char* data);
};

#endif // IPV4_H
