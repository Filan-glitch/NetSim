#include "host.h"
#include "cablenotfoundexception.h"
#include "router.h"

using namespace NetSim;

QMap<Port, Process*> Host::processTable() const { return m_processTable; }

QMap<IPv4Address, MACAddress> Host::hostTable() const { return m_hostTable; }

QMap<QString, IPv4Address> Host::domainTable() const { return m_domainTable; }

QMap<MACAddress, Router *> Host::cables() const { return m_cables; }

NetworkCard Host::networkCard() const { return m_networkCard; }

PackageTableModel *Host::packages() const { return m_packages; }

void Host::setPackages(PackageTableModel *packages) {
  this->m_packages = packages;
}

Process &Host::getProcessByName(const QString &name) {
  for (auto &process : m_processTable) {
        if (process->name() == name) {
      return *process;
    }
  }
  throw std::runtime_error("Process not found");
}

// Important for the processes to have access to the host
void Host::setHostOfProcesses(Host *host) {
  for (auto &process : m_processTable) {
        process->setHost(host);
  }
}

// Host always starts with the two standard processes HTTP(80) and DNS(53)
Host::Host(const NetworkCard &networkCard) : m_networkCard(networkCard) {
  Process http(Port(80), "HTTP");
  Process dns(Port(53), "DNS");
  addProcess(http);
  addProcess(dns);
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

void Host::addProcess(Process* process) {
  m_processTable[process.socket().sourcePort()] = process;
}

void Host::addIPAddress(const IPv4Address &ipAddress, const MACAddress &macAddress) {
  m_hostTable[ipAddress] = macAddress;
}

void Host::addMACAddress(const MACAddress &macAddress, Router *router) {
  m_cables[macAddress] = router;
}

void Host::addDomain(const QString &domain, const IPv4Address &ipAddress) {
  m_domainTable[domain] = ipAddress;
}
