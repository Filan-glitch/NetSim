#include "networkcard.h"
#include "src/protocols/ipv4.h"
#include "src/protocols/ethernet2.h"

using namespace NetSim;

NetworkCard::NetworkCard(const IPv4Address &networkAddress,
                         const MACAddress &physicalAddress)
    : m_networkAddress(networkAddress), m_physicalAddress(physicalAddress) {}

void NetworkCard::addIPHeader(Package &data, quint8 protocol,
                              const IPv4Address &destinationAddress) {
  quint16 id = QRandomGenerator::global()->generate();

  IPv4::initHeader(id, false, false, 0, 4, protocol, networkAddress(),
                   destinationAddress, data);
}

void NetworkCard::addMACHeader(Package &data, MACAddress destinationMACAddress,
                               quint16 etherType) {
  Ethernet2::initHeader(data, destinationMACAddress, this->physicalAddress(),
                  etherType);
}

IPv4Address NetworkCard::networkAddress() const { return m_networkAddress; }

MACAddress NetworkCard::physicalAddress() const { return m_physicalAddress; }
