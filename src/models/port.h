#ifndef PORT_H
#define PORT_H

#include <QString>

class Port
{
private:
    quint16 portNumber;
public:
    Port(quint16 portNumber);
    Port(){};
    quint16 getPortNumber() const;
    QVector<quint8> toArray() const;
    static Port getRandomPort();

    bool operator<(const Port& other)const;
};

#endif // PORT_H
