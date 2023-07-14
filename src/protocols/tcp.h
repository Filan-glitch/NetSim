#ifndef TCP_H
#define TCP_H

/**
 * @brief The TCP class
 * @par Represents the Transport Control Protocol
 */
class TCP
{
public:
    /**
     * @brief TCP
     */
    TCP();

    static void initHeader(int sourcePort, int destinationPort);
};

#endif // TCP_H
