#include "macaddress.h"

using namespace NetSim;

MACAddress::MACAddress(const RawData &address) : m_address(address) {}

// A function that returns the address formatted as a standard string (e.g.
// "00:00:00:00:00:00")
QString MACAddress::toString() const {
    QString address = "";
    for (int i = 0; i < 6; i++) {
        address += QString::number(static_cast<int>(m_address.getByte(i)), 16).toLower();
        if (i != 5) {
            address += ":";
        }
    }
    return address;
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
