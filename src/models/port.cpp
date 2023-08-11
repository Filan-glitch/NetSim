#include "port.h"
#include <QRandomGenerator>
#include <QVector>

Port::Port(quint16 portNumber) : m_portNumber(portNumber) {}

Port::Port(){};

quint16 Port::portNumber() const { return m_portNumber; }

QVector<quint8> Port::toArray() const {
  QVector<quint8> portArray;
  portArray.append(m_portNumber >> 8);
  portArray.append(m_portNumber & 0x00FF);
  return portArray;
}

Port Port::getRandomPort() {
  return Port(QRandomGenerator::global()->generate() % 65535);
}

bool Port::operator<(const Port &other) const {
  return this->m_portNumber < other.m_portNumber;
}
