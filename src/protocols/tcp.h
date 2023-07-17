#ifndef TCP_H
#define TCP_H

#include <cstdint>

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

    static void initHeader(int sourcePort, int destinationPort, int seqNumber, int ackNumber, bool ack,bool rst, bool syn, bool fin, int window);

private:
    static void setFlag(uint16_t* flags, bool set, int position);
};

#endif // TCP_H
