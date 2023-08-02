#ifndef MAC_H
#define MAC_H

#include <QString>
#include "src/models/macaddress.h"
#include "src/models/package.h"

/**
 * @brief The MAC class
 * @par Represents the MAC-Protocol
 */
class MAC
{
public:
    /**
     * @brief initHeader
     * @param data
     * @param destMACAdress
     * @param srcMACAdress
     * @param lengthField
     * @par Adds a MAC-Header to a package
     */
    static void initHeader(Package& data, MACAddress *destMACAdress, MACAddress *srcMACAdress, quint16 lengthField);

private:
    /**
     * @brief getFCS
     * @param destMACAdress
     * @param srcMACAdress
     * @param etherType
     * @param data
     * @return Frame Check Sequenz
     * @par Return the Frame Check Sequenz of a Ethernet II Header
     */
    static quint32 getFCS(MACAddress *destMACAdress, MACAddress *srcMACAdress, quint16 etherType, Package &data);
    /**
     * @brief calculateCRC32
     * @param data
     * @return Frame Check Sequenz
     * @par Requieres a QByteArray and calculates CRC32 with it
     */
    static quint32 calculateCRC32(const QByteArray &data);
};

#endif // MAC_H
