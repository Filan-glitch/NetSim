#include "socket.h"
#include "src/protocols/tcp.h"
#include "src/protocols/udp.h"



void Socket::addTCPHeader(Package &data, const IPAddress &srcAddress, const IPAddress &destAddress, bool ack, bool psh, bool syn, bool fin)
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

Port Socket::getSourcePort() const{
    return sourcePort;
}
void Socket::setSourcePort(const Port &sourcePort){
    this->sourcePort = sourcePort;
}
Port Socket::getDestinationPort() const{
    return destinationPort;
}
void Socket::setDestinationPort(const Port &destinationPort){
    this->destinationPort = destinationPort;
}

quint32 Socket::getStartSeq() const{
    return startSeq;
}
quint32 Socket::getServerSeq() const{
    return serverSeq;
}
quint32 Socket::getAmountReceivedData() const{
    return amountReceivedData;
}
