#include "router.h"
#include "cablenotfoundexception.h"
#include "src/protocols/headerutil.h"

using namespace NetSim;

IPAddress Router::globalIpAddress() const { return m_globalIpAddress; }

NetworkCard Router::networkCard() const { return m_networkCard; }

QMap<IPAddress, MACAddress> Router::macTable() const { return m_macTable; }

QMap<MACAddress, Router *> Router::routerCable() const { return m_routerCable; }

QMap<MACAddress, Host *> Router::hostCable() const { return m_hostCable; }

QMap<Port, NATEntry> Router::NAT() const { return m_portToNAT; }

void Router::addIPAddress(const IPAddress &ipAddress,
                          const MACAddress &macaddress) {
  m_macTable[ipAddress] = macaddress;
}

void Router::addMACAddress(const MACAddress &macAddress, Router *router) {
  m_routerCable[macAddress] = router;
}

void Router::addMACAddress(const MACAddress &macAddress, Host *host) {
  m_hostCable[macAddress] = host;
}

void Router::addNATEntry(const NATEntry &entry, const Port &port) {
  m_portToNAT[port] = entry;
  m_natToPort[entry] = port;
}

void Router::receivePackage(Package data) {
  qInfo() << "Router: " << this->networkCard().physicalAddress().toString()
          << " received a Package: " << data.info();
  IPAddress destIP = HeaderUtil::getIPAddressAsIPAddress(data, false);
  MACAddress destMAC = this->m_macTable[destIP];
  if (destIP == this->m_globalIpAddress) {
    NATEntry entry = m_portToNAT[HeaderUtil::getPortAsPort(data, false)];
    data.changePortAndIP(entry.port(), entry.address(), false);
    if (this->m_macTable.contains(entry.address())) {
      destMAC = this->m_macTable[entry.address()];
    }
  } else if (this->m_networkCard.networkAddress().toInt() != 0) {
    NATEntry entry(HeaderUtil::getIPAddressAsIPAddress(data, true),
                   HeaderUtil::getPortAsPort(data, true));
    data.changePortAndIP(m_natToPort[entry], this->m_globalIpAddress, true);
    qDebug() << "TEST TEST TEST 1";
  }

  data.changeEthernetHeader(this->m_networkCard.physicalAddress(), destMAC);
  qDebug() << "TEST TEST TEST 2";

  Router *nextRouter = this->m_routerCable[destMAC];
  if (nextRouter == nullptr) {
    Host *destHost = this->m_hostCable[destMAC];
    if (destHost == nullptr) {
      QString error = QString("Couldn't find a connection to MACAddress: %1")
                          .arg(destMAC.toString());
      qFatal("%s", error.toStdString().c_str());
      throw CableNotFoundException(error);
    }
    qInfo() << "Router: " << this->networkCard().physicalAddress().toString()
            << " sends Package to Host: "
            << destHost->networkCard().networkAddress().toString();
    destHost->receivePackage(data);
  } else {
    qInfo() << "Router: " << this->networkCard().physicalAddress().toString()
            << " sends Package to Router: "
            << nextRouter->m_networkCard.physicalAddress().toString();
    nextRouter->receivePackage(data);
  }
}
