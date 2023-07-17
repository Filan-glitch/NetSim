#ifndef PORT_H
#define PORT_H

#include <QString>

class Port
{
private:
    qint16 portNumber;
public:
    Port(qint16 portNumber);
    qint16 getPortNumber() const {
        return portNumber;
    }
};

#endif // PORT_H
