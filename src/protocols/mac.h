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
    static void initHeader(Package& data, const MACAddress &destMACAdress, const MACAddress &srcMACAdress, quint16 lengthField);
};

#endif // MAC_H
