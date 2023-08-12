#include "macaddress.h"

using namespace NetSim;

MACAddress::MACAddress(const QVector<quint8> &address) : m_address(address) {}

MACAddress::MACAddress() { m_address << 0 << 0 << 0 << 0 << 0 << 0; }

QString MACAddress::toString() const {
  return QString::number(static_cast<int>(m_address[0]), 16).toLower() + ":" +
         QString::number(static_cast<int>(m_address[1]), 16).toLower() + ":" +
         QString::number(static_cast<int>(m_address[2]), 16).toLower() + ":" +
         QString::number(static_cast<int>(m_address[3]), 16).toLower() + ":" +
         QString::number(static_cast<int>(m_address[4]), 16).toLower() + ":" +
         QString::number(static_cast<int>(m_address[5]), 16).toLower();
}

QVector<quint8> MACAddress::toArray() const { return m_address; }

quint64 MACAddress::toInt() const {
  quint64 returnAddress = m_address[0];
  returnAddress = (returnAddress << 8) + m_address[1];
  returnAddress = (returnAddress << 8) + m_address[2];
  returnAddress = (returnAddress << 8) + m_address[3];
  returnAddress = (returnAddress << 8) + m_address[4];
  returnAddress = (returnAddress << 8) + m_address[5];
  return returnAddress;
}

MACAddress MACAddress::getRandomAddress() {
  static QRandomGenerator *generator = new QRandomGenerator(2183193);
  QVector<quint8> addressArray;
  for (int i = 0; i < 6; i++) {
    addressArray.append(generator->generate() % 256);
  }
  return MACAddress(addressArray);
}

bool MACAddress::operator<(const MACAddress &other) const {
  return toInt() < other.toInt();
}

bool MACAddress::operator==(const MACAddress &other) const {
  return this->toInt() == other.toInt();
}
