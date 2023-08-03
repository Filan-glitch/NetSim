#ifndef UDP_H
#define UDP_H

/**
 * @brief The UDP class
 * @par represents the User Datagram Protocol
 */
class UDP
{
public:
    /**
     * @brief UDP
     */
    UDP();

    static void initHeader(int sourcePort, int destinationPort);
};

#endif // UDP_H
