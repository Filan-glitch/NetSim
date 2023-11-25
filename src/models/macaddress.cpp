#include "macaddress.h"

using namespace NetSim;

MACAddress::MACAddress(const QBitArray &address) : m_address(address) {}

// A function that returns the address formatted as a standard string (e.g.
// "00:00:00:00:00:00")
QString MACAddress::toString() const {
  return QString::number(static_cast<int>(m_address[0]), 16).toLower() + ":" +
         QString::number(static_cast<int>(m_address[1]), 16).toLower() + ":" +
         QString::number(static_cast<int>(m_address[2]), 16).toLower() + ":" +
         QString::number(static_cast<int>(m_address[3]), 16).toLower() + ":" +
         QString::number(static_cast<int>(m_address[4]), 16).toLower() + ":" +
         QString::number(static_cast<int>(m_address[5]), 16).toLower();
}

QBitArray MACAddress::data() const { return m_address; }

// Using the random generation method by Qt to generate a random address
MACAddress MACAddress::getRandomAddress() {
  QBitArray addressArray(48);
  for (int i = 0; i < 48; i++) {
    addressArray[i] = QRandomGenerator::global()->bounded(2);
  }
  return MACAddress(addressArray);
}

bool MACAddress::operator<(const MACAddress &other) const {
  return toInt() < other.toInt();
}

bool MACAddress::operator==(const MACAddress &other) const {
  return this->toInt() == other.toInt();
}
