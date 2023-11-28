#include "port.h"
#include <QRandomGenerator>

using namespace NetSim;

Port::Port(quint16 portNumber) : m_portNumber(portNumber) {}

Port::Port(RawData portNumber) : m_portNumber(static_cast<quint16>(portNumber)){}


quint16 Port::portNumber() const
{
    return m_portNumber;
}

RawData Port::data() const {
    RawData data;
    data << m_portNumber;
    return data;
}

// Using random generation by Qt to generate a random port number
Port Port::getRandomPort() {
  return Port(QRandomGenerator::global()->generate() % 65535);
}
