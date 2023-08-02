#include "socket.h"
#include "src/protocols/tcp.h"
#include "src/protocols/udp.h"



void Socket::addTCPHeader(Package &data)
{
    //TODO HEADER INITIALISIERUNG

}

void Socket::addUDPHeader(Package &data)
{
    //TODO  Daten richtig ausfüllen
    UDP::initHeader(this->sourcePort, this->destinationPort,0,data);
}

void Socket::sentPackageToNetworkCard(Package &data)
{
    
}

Socket::Socket(const Port &sourcePort, const Port &destinationPort) : sourcePort(sourcePort),
    destinationPort(destinationPort)
{}

Socket::Socket() : sourcePort(Port(0)), destinationPort(Port(0)) {

}
