#include "port.h"
#include <QRandomGenerator>
#include <QVector>

Port::Port(quint16 portNumber) : portNumber(portNumber) {}

quint16 Port::getPortNumber() const {
    return portNumber;
}

QVector<quint8> Port::toArray() const
{
    QVector<quint8> portArray;
    portArray.append(portNumber >> 8);
    portArray.append(portNumber & 0x00FF);
    return portArray;
}

Port Port::getRandomPort() {
    return Port(QRandomGenerator::global()->generate() % 65535);
}

bool Port::operator<(const Port &other) const{
    return this->portNumber < other.portNumber;
}
