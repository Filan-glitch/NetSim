#ifndef SOCKET_H
#define SOCKET_H

#include "src/models/ipaddress.h"
#include "src/models/package.h"
#include "src/models/port.h"

namespace NetSim {

class Port;

class Socket {
public:
  Socket();

  Socket(const Port &sourcePort, const Port &destinationPort);

  void addTCPHeader(Package &data, const IPAddress &srcAddress,
                    const IPAddress &destAddress, bool ack, bool psh, bool syn,
                    bool fin);

  void addUDPHeader(Package &data);

  Port sourcePort() const;

  void setSourcePort(const Port &sourcePort);

  Port destinationPort() const;

  void setDestinationPort(const Port &destinationPort);

  quint32 startSeq() const;

  quint32 serverSeq() const;

  quint32 amountReceivedData() const;

private:
  Port m_sourcePort;

  Port m_destinationPort;

  quint32 m_startSeq{100};

  quint32 m_serverSeq;

  quint32 m_amountReceivedData{0};
};
} // namespace NetSim

#endif // SOCKET_H
