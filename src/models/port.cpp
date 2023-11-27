#include "port.h"
#include <QRandomGenerator>

using namespace NetSim;

Port::Port(RawData portNumber) : m_portNumber(portNumber) {}

Port::Port(quint16 portNumber) {
  m_portNumber.setByte(0, portNumber & 0xFF);
  m_portNumber.setByte(1, (portNumber >> 8) & 0xFF);
}


quint16 Port::portNumber() const
{
    quint16 portNumber = 0;
    portNumber += m_portNumber.getByte(1) << 8;
    portNumber += m_portNumber.getByte(0);
    return portNumber;
}

RawData Port::data() const {
  return m_portNumber;
}

// Using random generation by Qt to generate a random port number
Port Port::getRandomPort() {
  return Port(QRandomGenerator::global()->generate() % 65535);
}
