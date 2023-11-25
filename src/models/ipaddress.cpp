#include "ipaddress.h"

using namespace NetSim;

IPAddress::IPAddress(const QBitArray &address) : m_address(address) {}

// A function that returns the address formatted as a standard string (e.g.
// 101.221.23.1)
QString IPAddress::toString() const {
  return QString::number(static_cast<int>(m_address[0])) + "." +
         QString::number(static_cast<int>(m_address[1])) + "." +
         QString::number(static_cast<int>(m_address[2])) + "." +
         QString::number(static_cast<int>(m_address[3]));
}

QBitArray IPAddress::toArray() const { return m_address; }

// Using the random generation method by Qt to generate a random address
IPAddress IPAddress::getRandomAddress(bool isLocal) {
  QBitArray addressArray(32);
  for (int i = 0; i < 32; i++) {
    addressArray[i] = QRandomGenerator::global()->bounded(2);
  }
  // If a local address is required, set the non subnetmask byte to 1
  if (isLocal) {
    addressArray[31] = true;
    addressArray[30] = false;
    addressArray[29] = false;
    addressArray[28] = false;
    addressArray[27] = false;
    addressArray[26] = false;
    addressArray[25] = false;
    addressArray[24] = false;
  }
  return IPAddress(addressArray);
}

bool IPAddress::operator==(const IPAddress &other) const {
  return this->m_address == other.m_address;
}
