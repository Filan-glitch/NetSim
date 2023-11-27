#include "macaddress.h"

using namespace NetSim;

MACAddress::MACAddress(const RawData &address) : m_address(address) {}

// A function that returns the address formatted as a standard string (e.g.
// "00:00:00:00:00:00")
QString MACAddress::toString() const {
    return QString::number(static_cast<int>(m_address.getByte(0)), 16).toLower() + ":" +
           QString::number(static_cast<int>(m_address.getByte(1)), 16).toLower() + ":" +
           QString::number(static_cast<int>(m_address.getByte(2)), 16).toLower() + ":" +
           QString::number(static_cast<int>(m_address.getByte(3)), 16).toLower() + ":" +
           QString::number(static_cast<int>(m_address.getByte(4)), 16).toLower() + ":" +
           QString::number(static_cast<int>(m_address.getByte(5)), 16).toLower();
}

RawData MACAddress::data() const { return m_address; }

// Using the random generation method by Qt to generate a random address
MACAddress MACAddress::getRandomAddress() {
  RawData addressArray(48);
  for (int i = 0; i < 48; i++) {
      addressArray.setBit(i, QRandomGenerator::global()->bounded(2));
  }
  return MACAddress(addressArray);
}
