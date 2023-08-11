#ifndef PORT_H
#define PORT_H

#include <QString>

namespace NetSim {
class Port;
}

class Port {
public:
  Port();

  Port(quint16 portNumber);

  quint16 portNumber() const;

  QVector<quint8> toArray() const;

  static Port getRandomPort();

  bool operator<(const Port &other) const;

private:
  quint16 m_portNumber;
};

#endif // PORT_H
