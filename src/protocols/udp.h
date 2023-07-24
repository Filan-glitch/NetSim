#ifndef UDP_H
#define UDP_H

#include "../models/port.h"
#include "../models/package.h"
#include <cstdint>
#include <QString>

using namespace std;

/**
 * @brief The UDP class
 * @par Represents the User Datagram Protocol
 */
class UDP
{
public:
    /**
    * @brief UDP::initHeader
    * @param sourcePort
    * @param destinationPort
    * @param dataLength
    * @param data
    * @par Initilizes an UDP Package and calculates its checksum
    */
    static void initHeader(const Port &sourcePort, const Port &destinationPort, qint16 length, Package& data);

private:
    static qint16 getChecksum(const char* data, qint16 length, qint16 sourcePort, qint16 destinationPort);
    static qint16 overflowHandling(qint16 checksum);
};

#endif // UDP_H
