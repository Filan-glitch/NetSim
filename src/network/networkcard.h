#ifndef NETWORKCARD_H
#define NETWORKCARD_H

#include "src/models/ipaddress.h"
#include "src/models/macaddress.h"
#include "src/models/package.h"

namespace NetSim {
class NetworkCard;
}

class NetworkCard {
public:
  NetworkCard(const IPAddress &networkAddress,
              const MACAddress &physicalAddress);

  void addIPHeader(Package &data, quint8 protocol,
                   const IPAddress &destinationAddress);

  void addMACHeader(Package &data, MACAddress destinationMACAddress,
                    quint16 dataLength);

  IPAddress networkAddress() const;

  MACAddress physicalAddress() const;

private:
  IPAddress m_networkAddress;

  MACAddress m_physicalAddress;
};

#endif // NETWORKCARD_H
