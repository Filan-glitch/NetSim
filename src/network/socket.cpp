#include "socket.h"
#include "src/protocols/tcp.h"
#include "src/protocols/udp.h"

Socket::Socket(Port port):port(port)
{

}

void Socket::addTCPHeader(Package& data)
{
    //TODO HEADER INITIALISIERUNG
    //TCP::initHeader()
}

void Socket::addUDPHeader(Package& data)
{
    //TODO  Daten richtig ausfüllen
    UDP::initHeader(this->port,80,0,data);
}
