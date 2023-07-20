#ifndef SOCKET_H
#define SOCKET_H

#include <src/models/package.h>
#include <src/models/port.cpp>



class Socket
{
public:
    Socket(Port port);

    void addTCPHeader(Package& data);
    void addUDPHeader(Package& data);
    void sentPackageToNetworkCard(Package& data);
private:
    Port port;
};

#endif // SOCKET_H
