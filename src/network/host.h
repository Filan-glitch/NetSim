#ifndef HOST_H
#define HOST_H

#include "src/management/packagetablemodel.h"
#include "src/models/ipaddress.h"
#include "src/models/macaddress.h"
#include "src/models/process.h"
#include "src/network/networkcard.h"
#include <QMap>
#include <QString>

namespace NetSim {
class Host;
}

class Router;

class Host {
public:
  Host(const NetworkCard &networkCard);

  QMap<Port, Process> processTable() const;

  QMap<IPAddress, MACAddress> hostTable() const;

  QMap<QString, IPAddress> domainTable() const;

  QMap<MACAddress, Router *> cables() const;

  NetworkCard networkCard() const;

  Router *getRouterByMACAddress(const MACAddress &destinationAddress);

  void sendPackage(Package &data, const MACAddress &destinationAddress);

  virtual void receivePackage(Package data) = 0;

  void addProcess(const Port &port, const Process &process);

  void addIPAddress(const IPAddress &ipAddress, const MACAddress &macAddress);

  void addMACAddress(const MACAddress &macAddress, Router *router);

  void addDomain(const QString &domain, const IPAddress &ipAddress);

  PackageTableModel *packages() const;

  void setPackages(PackageTableModel *packages);

  Process &getProcessByName(const QString &name);

  void setHostOfProcesses(Host *host);

private:
  QMap<Port, Process> m_processTable;

  QMap<IPAddress, MACAddress> m_hostTable;

  QMap<QString, IPAddress> m_domainTable;

  QMap<MACAddress, Router *> m_cables;

  NetworkCard m_networkCard;

  PackageTableModel *m_packages;
};

#endif // HOST_H
