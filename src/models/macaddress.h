#ifndef MACADDRESS_H
#define MACADDRESS_H

#include <QRandomGenerator>
#include <QString>
#include <QVector>

namespace NetSim {
class MACAddress;
}

class MACAddress {
public:
  MACAddress(const QVector<quint8> &address);

  MACAddress();

  QString toString() const;

  QVector<quint8> toArray() const;

  quint64 toInt() const;

  static MACAddress getRandomAddress();

  bool operator<(const MACAddress &other) const;

  bool operator==(const MACAddress &other) const;

private:
  QVector<quint8> m_address;
};

#endif // MACADDRESS_H
