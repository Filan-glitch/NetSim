#ifndef TCP_H
#define TCP_H

#include "src/models/port.h"
#include "src/models/package.h"
#include "src/models/ipaddress.h"
#include <cstdint>
#include <QString>
#include <QDebug>

/**
 * @brief The TCP class
 * @par Represents the Transport Control Protocol
 */
class TCP
{
public:
    /**
     * @brief initHeader
     * @param srcAdress
     * @param destAdress
     * @param sourcePort
     * @param destinationPort
     * @param seqNumber
     * @param ackNumber
     * @param ack
     * @param rst
     * @param syn
     * @param fin
     * @param window
     * @param data
     * @param dataLength
     * @par adds a TCP-Header to a package and calculates its checksum
     */
    static void initHeader(const IPAddress &srcAdress, const IPAddress &destAdress, const Port &sourcePort, const Port &destinationPort, quint32 seqNumber, quint32 ackNumber, bool ack,bool rst, bool syn, bool fin, quint16 window, Package& data, quint16 dataLength);

private:
    static void setFlag(quint16* flags, bool set, quint16 position);
    static quint16 getTCPChecksum(quint8* sourceAddress, quint8* destinationAddress, quint16 sourcePort, quint16 destinationPort, quint32 seqNumber, quint32 ackNumber, quint16 flags, const char* data, quint16 dataLength);
};

#endif // TCP_H
