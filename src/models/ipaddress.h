#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QRandomGenerator>
#include <QString>
#include <QTextStream>
#include <QVector>

namespace NetSim {
class IPAddress;
}

class IPAddress {
public:
  IPAddress();

  IPAddress(const QVector<quint8> &address);

  QString toString() const;

  QVector<quint8> toArray() const;

  quint32 toInt() const;

  static IPAddress getRandomAddress(bool isLocal = false);

  bool operator<(const IPAddress &other) const;

  bool operator==(const IPAddress &other) const;

private:
  QVector<quint8> m_address;
};

#endif // IPADDRESS_H
