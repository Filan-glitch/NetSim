#ifndef TCP_H
#define TCP_H

#include "src/models/port.h"
#include <cstdint>
#include <QString>

/**
 * @brief The TCP class
 * @par Represents the Transport Control Protocol
 */
class TCP
{
public:
    static void initHeader(Port sourcePort, Port destinationPort, qint32 seqNumber, qint32 ackNumber, bool ack,bool rst, bool syn, bool fin, qint16 window);

private:
    static void setFlag(qint16* flags, bool set, qint16 position);
};

#endif // TCP_H
