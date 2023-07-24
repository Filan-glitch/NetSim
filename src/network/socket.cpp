#include "socket.h"
#include "../protocols/tcp.h"
#include "../protocols/udp.h"



void Socket::addTCPHeader(Package& data)
{
    //TODO HEADER INITIALISIERUNG

}

void Socket::addUDPHeader(Package& data)
{
    //TODO  Daten richtig ausfüllen
    UDP::initHeader(this->sourcePort, this->destinationPort,0,data);
}

Socket::Socket(const Port &sourcePort, const Port &destinationPort) : sourcePort(sourcePort),
    destinationPort(destinationPort)
{}
