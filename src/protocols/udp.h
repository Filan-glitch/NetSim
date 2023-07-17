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

    static void initHeader(int sourcePort, int destinationPort,size_t length, char* data);

private:
    static int getChecksum(char* data, size_t length, int sourcePort, int destinationPort);
    static int overflowHandling(int checksum);
};

#endif // UDP_H
