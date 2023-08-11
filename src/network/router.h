#ifndef ROUTER_H
#define ROUTER_H

#include "host.h"
#include "natentry.h"
#include "src/models/ipaddress.h"
#include "src/network/networkcard.h"
#include <QHash>
#include <QStack>
#include <QString>

namespace NetSim {
class Router;
}

class Host;

class Router {
public:
  Router();

  void receivePackage(Package data);

  IPAddress globalIpAddress() const;

  NetworkCard networkCard() const;

  QMap<IPAddress, MACAddress> macTable() const;

  QMap<MACAddress, Router *> routerCable() const;

  QMap<MACAddress, Host *> hostCable() const;

  QMap<Port, NATEntry> NAT() const;

  void addIPAddress(const IPAddress &ipAddress, const MACAddress &macaddress);

  void addMACAddress(const MACAddress &macAddress, Router *router);

  void addMACAddress(const MACAddress &macAddress, Host *host);

  void addNATEntry(const NATEntry &entry, const Port &port);

private:
  QMap<IPAddress, MACAddress> m_macTable;

  QMap<MACAddress, Router *> m_routerCable;

  QMap<MACAddress, Host *> m_hostCable;

  QMap<Port, NATEntry> m_portToNAT;

  QMap<NATEntry, Port> m_natToPort;

  NetworkCard m_networkCard;

  IPAddress m_globalIpAddress;
};

#endif // ROUTER_H
