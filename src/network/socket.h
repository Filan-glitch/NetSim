#ifndef SOCKET_H
#define SOCKET_H

#include "src/models/package.h"
#include "src/models/port.h"
#include "src/models/ipaddress.h"



class Socket
{
public:
    Socket();
    Socket(const Port &sourcePort, const Port &destinationPort);

    void addTCPHeader(Package &data, IPAddress srcAddress, IPAddress destAddress, bool ack, bool psh, bool syn, bool fin);
    void addUDPHeader(Package& data);
private:
    Port sourcePort;
    Port destinationPort;
    quint32 startSeq = 100;
    quint32 serverSeq;
    quint32 amountReceivedData = 0;
};

#endif // SOCKET_H
