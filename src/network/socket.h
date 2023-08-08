#ifndef SOCKET_H
#define SOCKET_H

#include "src/models/package.h"
#include "src/models/ipaddress.h"
#include "src/models/port.h"

class Port;

class Socket
{
public:
    Socket();
    Socket(const Port &sourcePort, const Port &destinationPort);

    void addTCPHeader(Package &data, IPAddress srcAddress, IPAddress destAddress, bool ack, bool psh, bool syn, bool fin);
    void addUDPHeader(Package& data);
    Port getSourcePort();
    void setSourcePort(Port sourcePort);
    Port getDestinationPort();
    quint32 getStartSeq();
    quint32 getServerSeq();
    quint32 getAmountReceivedData();
private:
    Port sourcePort;
    Port destinationPort;
    quint32 startSeq = 100;
    quint32 serverSeq;
    quint32 amountReceivedData = 0;
};

#endif // SOCKET_H
