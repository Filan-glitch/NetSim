#ifndef SOCKET_H
#define SOCKET_H

#include "../models/package.h"
#include "../models/port.h"



class Socket
{
public:
    Socket(const Port &sourcePort, const Port &destinationPort);

    void addTCPHeader(Package& data);
    void addUDPHeader(Package& data);
    void sentPackageToNetworkCard(Package& data);
private:
    Port sourcePort;
    Port destinationPort;
};

#endif // SOCKET_H
