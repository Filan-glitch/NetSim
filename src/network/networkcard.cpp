#include "networkcard.h"
#include "qdatetime.h"
#include "src/protocols/ipv4.h"
#include "src/protocols/mac.h"

NetworkCard::NetworkCard(const IPAddress &networkAddress,
                         const MACAddress &physicalAddress)
    : m_networkAddress(networkAddress), m_physicalAddress(physicalAddress) {}

void NetworkCard::addIPHeader(Package &data, quint8 protocol,
                              const IPAddress &destinationAddress) {
  QTime seed;
  QRandomGenerator rnd(seed.msecsSinceStartOfDay());
  quint16 id = rnd.generate();

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
