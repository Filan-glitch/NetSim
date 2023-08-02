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
    static void initHeader(const Port &sourcePort, const Port &destinationPort, quint16 length, Package &data);

private:
    static quint16 getChecksum(const char* data, quint16 length, quint16 sourcePort, quint16 destinationPort);
    static quint16 overflowHandling(quint16 checksum);
};

#endif // UDP_H
