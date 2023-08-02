#include "port.h"



Port::Port(quint16 portNumber) : portNumber(portNumber) {}

quint16 Port::getPortNumber() const {
    return portNumber;
}
