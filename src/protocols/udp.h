#ifndef UDP_H
#define UDP_H

#include "src/models/port.h"
#include "src/models/package.h"
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
    static void initHeader(Port sourcePort, Port destinationPort, size_t length, Package data);

private:
    static qint16 getChecksum(const char* data, size_t length, Port sourcePort, Port destinationPort);
    static qint16 overflowHandling(qint16 checksum);
};

#endif // UDP_H
