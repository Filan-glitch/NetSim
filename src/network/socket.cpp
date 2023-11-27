#include "socket.h"
#include "src/protocols/tcp.h"
#include "src/protocols/udp.h"

using namespace NetSim;

void Socket::addTCPHeader(Package &data, const IPv4Address &srcAddress,
                          const IPv4Address &destAddress, bool ack, bool psh,
                          bool syn, bool fin) {
  TCP::initHeader(srcAddress, destAddress, this->m_sourcePort,
                  this->m_destinationPort, m_startSeq + m_amountReceivedData,
                  m_serverSeq + m_amountReceivedData, ack, psh, syn, fin, 512,
                  data);
}

void Socket::addUDPHeader(Package &data) {
  UDP::initHeader(this->m_sourcePort, this->m_destinationPort, data);
}

Socket::Socket(const Port &sourcePort, const Port &destinationPort)
    : m_sourcePort(sourcePort), m_destinationPort(destinationPort) {}

Port Socket::sourcePort() const { return m_sourcePort; }
void Socket::setSourcePort(const Port &sourcePort) {
  this->m_sourcePort = sourcePort;
}
Port Socket::destinationPort() const { return m_destinationPort; }
void Socket::setDestinationPort(const Port &destinationPort) {
  this->m_destinationPort = destinationPort;
}

quint32 Socket::startSeq() const { return m_startSeq; }
quint32 Socket::serverSeq() const { return m_serverSeq; }
quint32 Socket::amountReceivedData() const { return m_amountReceivedData; }
