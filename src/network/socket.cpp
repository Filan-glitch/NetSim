#include "socket.h"
#include "src/protocols/tcp.h"
#include "src/protocols/udp.h"



void Socket::addTCPHeader(Package &data, IPAddress srcAddress, IPAddress destAddress, bool ack, bool psh, bool syn, bool fin)
{
    TCP::initHeader(srcAddress, destAddress, this->sourcePort, this->destinationPort,startSeq+amountReceivedData,serverSeq+amountReceivedData, ack, psh, syn, fin,512,data,data.getData().length());
}

void Socket::addUDPHeader(Package &data)
{
    UDP::initHeader(this->sourcePort, this->destinationPort,0,data);
}

Socket::Socket(const Port &sourcePort, const Port &destinationPort) : sourcePort(sourcePort),
    destinationPort(destinationPort)
{}

Socket::Socket() : sourcePort(Port(0)), destinationPort(Port(0)) {

}
