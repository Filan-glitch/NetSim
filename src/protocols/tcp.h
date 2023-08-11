#ifndef TCP_H
#define TCP_H

#include "src/models/ipaddress.h"
#include "src/models/package.h"
#include "src/models/port.h"
#include <QDebug>
#include <QString>
#include <QVector>

namespace NetSim {
enum TCPFlag {
  FIN = 0,
  SYN = 1,
  RST = 2,
  PSH = 3,
  ACK = 4,
  URG = 5,
  ECE = 6,
  CWR = 7,
  NS = 8
};
class TCP;
} // namespace NetSim

class TCP {
public:
  static void initHeader(const IPAddress &srcAdress,
                         const IPAddress &destAdress, const Port &sourcePort,
                         const Port &destinationPort, quint32 seqNumber,
                         quint32 ackNumber, bool ack, bool rst, bool syn,
                         bool fin, quint16 window, Package &data);

private:
  static void setFlag(quint16 *flags, bool set, quint16 position);

  static quint16 getTCPChecksum(const QVector<quint8> &sourceAddress,
                                const QVector<quint8> &destinationAddress,
                                quint16 sourcePort, quint16 destinationPort,
                                quint32 seqNumber, quint32 ackNumber,
                                quint16 flags, const char *data,
                                quint16 dataLength);
};

#endif // TCP_H
