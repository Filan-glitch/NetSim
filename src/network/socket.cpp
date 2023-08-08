#include "socket.h"
#include "src/protocols/tcp.h"
#include "src/protocols/udp.h"



void Socket::addTCPHeader(Package &data, IPAddress srcAddress, IPAddress destAddress, bool ack, bool psh, bool syn, bool fin)
{
    TCP::initHeader(srcAddress, destAddress, this->sourcePort, this->destinationPort,startSeq+amountReceivedData,serverSeq+amountReceivedData, ack, psh, syn, fin,512,data);
}

void Socket::addUDPHeader(Package &data)
{
    UDP::initHeader(this->sourcePort, this->destinationPort,data);
}

Socket::Socket(const Port &sourcePort, const Port &destinationPort) : sourcePort(sourcePort),
    destinationPort(destinationPort)
{}

Socket::Socket() : sourcePort(Port(0)), destinationPort(Port(0)) {

}

Port Socket::getSourcePort(){
    return sourcePort;
}
void Socket::setSourcePort(Port sourcePort){
    this->sourcePort = sourcePort;
}
Port Socket::getDestinationPort(){
    return destinationPort;
}

quint32 Socket::getStartSeq(){
    return startSeq;
}
quint32 Socket::getServerSeq(){
    return serverSeq;
}
quint32 Socket::getAmountReceivedData(){
    return amountReceivedData;
}
