#ifndef UDP_H
#define UDP_H

#include <cstdint>

using namespace std;

/**
 * @brief The UDP class
 * @par Represents the User Datagram Protocol
 */
class UDP
{
public:
    /**
     * @brief UDP
     */
    UDP();

    /**
    * @brief UDP::initHeader
    * @param sourcePort
    * @param destinationPort
    * @param dataLength
    * @param data
    * @par Initilizes an UDP Package and calculates its checksum
    */
    static void initHeader(int sourcePort, int destinationPort,size_t length, char* data);

private:
    static int getChecksum(char* data, size_t length, int sourcePort, int destinationPort);
    static int overflowHandling(int checksum);
};

#endif // UDP_H
