#include "networkcard.h"
#include "src/software/03_network_layer/ipv4.h"
#include "src/software/04_network_access_layer/mac.h"

using namespace NetSim;

NetworkCard::NetworkCard(const IPAddress &networkAddress,
                         const MACAddress &physicalAddress)
    : m_networkAddress(networkAddress), m_physicalAddress(physicalAddress) {}

void NetworkCard::addIPHeader(Package &data, quint8 protocol,
                              const IPAddress &destinationAddress) {
  quint16 id = QRandomGenerator::global()->generate();

  IPv4::initHeader(id, false, false, 0, 4, protocol, networkAddress(),
                   destinationAddress, data);
}

void NetworkCard::addMACHeader(Package &data, MACAddress destinationMACAddress,
                               quint16 etherType) {
  MAC::initHeader(data, destinationMACAddress, this->physicalAddress(),
                  etherType);
}

IPAddress NetworkCard::networkAddress() const { return m_networkAddress; }

MACAddress NetworkCard::physicalAddress() const { return m_physicalAddress; }
