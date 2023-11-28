#include "ipv4address.h"

using namespace NetSim;

IPv4Address::IPv4Address(const RawData &address) : m_address(address) {}

// A function that returns the address formatted as a standard string (e.g.
// 101.221.23.1)
QString IPv4Address::toString() const {
  return QString::number(static_cast<int>(m_address.getByte(0))) + "." +
         QString::number(static_cast<int>(m_address.getByte(1))) + "." +
         QString::number(static_cast<int>(m_address.getByte(2))) + "." +
         QString::number(static_cast<int>(m_address.getByte(3)));
}

RawData IPv4Address::address() const { return m_address; }

// Using the random generation method by Qt to generate a random address
IPv4Address IPv4Address::getRandomAddress(bool isLocal) {
  RawData address(32);
  for (int i = 0; i < 32; i++) {
      address.setBit(i, QRandomGenerator::global()->bounded(2));
  }
  // If a local address is required, set the non subnetmask byte to 1
  if (isLocal) {
      address.setByte(3, 1);
  }
  return IPv4Address(address);
}
