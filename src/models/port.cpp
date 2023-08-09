#include "port.h"
#include <QRandomGenerator>

Port::Port(quint16 portNumber) : portNumber(portNumber) {}

quint16 Port::getPortNumber() const {
    return portNumber;
}

Port Port::getRandomPort() {
    return Port(QRandomGenerator::global()->generate() % 65535);
}
