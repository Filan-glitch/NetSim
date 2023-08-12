#include "host.h"
#include "cablenotfoundexception.h"
#include "router.h"

using namespace NetSim;

QMap<Port, Process> Host::processTable() const { return m_processTable; }

QMap<IPAddress, MACAddress> Host::hostTable() const { return m_hostTable; }

QMap<QString, IPAddress> Host::domainTable() const { return m_domainTable; }

QMap<MACAddress, Router *> Host::cables() const { return m_cables; }

NetworkCard Host::networkCard() const { return m_networkCard; }

PackageTableModel *Host::packages() const { return m_packages; }

void Host::setPackages(PackageTableModel *packages) {
  this->m_packages = packages;
}

Process &Host::getProcessByName(const QString &name) {
  for (auto &process : m_processTable) {
    if (process.name() == name) {
      return process;
    }
  }
  throw std::runtime_error("Process not found");
}

void Host::setHostOfProcesses(Host *host) {
  for (auto &process : m_processTable) {
    process.setHost(host);
  }
}

Host::Host(const NetworkCard &networkCard)
    : m_processTable(QMap<Port, Process>()),
      m_hostTable(QMap<IPAddress, MACAddress>()),
      m_domainTable(QMap<QString, IPAddress>()),
      m_cables(QMap<MACAddress, Router *>()), m_networkCard(networkCard),
      m_packages(nullptr) {
  Process http(Port(80), "HTTP");
  Process dns(Port(53), "DNS");
  addProcess(http.getSocket().sourcePort(), http);
  addProcess(dns.getSocket().sourcePort(), dns);
}

Router *Host::getRouterByMACAddress(const MACAddress &destinationAddress) {
  if (m_cables[destinationAddress] != nullptr) {
    return m_cables[destinationAddress];
  } else {
    throw CableNotFoundException(
        "Cable not found in: Host::getRouterByMACAddress");
  }
}

void Host::sendPackage(Package &data, const MACAddress &destinationAddress) {
  m_cables[destinationAddress]->receivePackage(data);
}

void Host::addProcess(const Port &port, const Process &process) {
  m_processTable[port] = process;
}

void Host::addIPAddress(const IPAddress &ipAddress,
                        const MACAddress &macAddress) {
  m_hostTable[ipAddress] = macAddress;
}

void Host::addMACAddress(const MACAddress &macAddress, Router *router) {
  m_cables[macAddress] = router;
}

void Host::addDomain(const QString &domain, const IPAddress &ipAddress) {
  m_domainTable[domain] = ipAddress;
}
