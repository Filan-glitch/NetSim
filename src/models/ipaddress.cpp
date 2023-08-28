#include "ipaddress.h"

using namespace NetSim;

IPAddress::IPAddress(const QVector<quint8> &address) : m_address(address) {}

// A function that returns the address formatted as a standard string (e.g.
// 101.221.23.1)
QString IPAddress::toString() const {
  return QString::number(static_cast<int>(m_address[0])) + "." +
         QString::number(static_cast<int>(m_address[1])) + "." +
         QString::number(static_cast<int>(m_address[2])) + "." +
         QString::number(static_cast<int>(m_address[3]));
}

QVector<quint8> IPAddress::toArray() const { return m_address; }

// A function that returns the address formatted as a quint32 (e.g. 0x65DD1701)
quint32 IPAddress::toInt() const {
  quint32 returnAddress = m_address[0];
  returnAddress = (returnAddress << 8) + m_address[1];
  returnAddress = (returnAddress << 8) + m_address[2];
  returnAddress = (returnAddress << 8) + m_address[3];
  return returnAddress;
}

// Using the random generation method by Qt to generate a random address
IPAddress IPAddress::getRandomAddress(bool isLocal) {
  static QRandomGenerator *generator = new QRandomGenerator(2183193);
  QVector<quint8> addressArray;
  for (int i = 0; i < 4; i++) {
    addressArray.append(generator->generate() % 256);
  }
  // If a local address is required, set the non subnetmask byte to 1
  if (isLocal)
    addressArray[3] = 1;
  return IPAddress(addressArray);
}

bool IPAddress::operator<(const IPAddress &other) const {
  return toInt() < other.toInt();
}

bool IPAddress::operator==(const IPAddress &other) const {
  quint32 otherAddressInt = other.toInt();
  return otherAddressInt == toInt();
}
