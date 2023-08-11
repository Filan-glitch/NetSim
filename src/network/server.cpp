#include "server.h"
#include "cablenotfoundexception.h"
#include "router.h"

#include <src/protocols/headerutil.h>

Server::Server(const NetworkCard &networkCard, const QString &domain,
               const QString &html)
    : Host(networkCard), m_domain(domain) {
  this->m_htmlFile = html;
}

QString Server::domain() const { return m_domain; }

QString Server::htmlFile() const { return this->m_htmlFile; }

void Server::receivePackage(Package data) {
  qInfo() << "Server: " << this->networkCard().networkAddress().toString()
          << " received a Package: " << data.info();
  packages()->addPackage(data);

  if (HeaderUtil::getTopProtocol(data) == NetSim::HeaderType::DNS) {
    Process dnsProcess;
    try {
      dnsProcess = getProcessByName("DNS");
    } catch (const std::runtime_error &re) {
      qDebug() << "Could not find Process DNS in Server::receivePackage DNS "
                  "Request Package";
      return;
    }

    Package dnsResponse = dnsProcess.generateDNSResponsePackage(
        HeaderUtil::getIPAddressAsIPAddress(data, true),
        HeaderUtil::getDNSQuery(data, 0, NetSim::RRAttribute::NAME),
        HeaderUtil::getPortAsPort(data, true));

    MACAddress routerMAC = this->hostTable().value(
        HeaderUtil::getIPAddressAsIPAddress(data, true));
    Router *router;
    try {
      router = this->getRouterByMACAddress(routerMAC);
    } catch (const CableNotFoundException &cnfe) {
      qDebug() << cnfe.errorMessage()
               << " in Server::receivePackage creating DNS Response";
      return;
    }

    if (router == nullptr) {
      qDebug() << "Router is nullptr in Server::receivePackage";
      return;
    }

    qInfo() << "Server: " << this->networkCard().networkAddress().toString()
            << " sends DNSResponse to Router: "
            << router->networkCard().physicalAddress().toString();
    router->receivePackage(dnsResponse);
    return;
  }

  if (HeaderUtil::getTCPFlag(data, NetSim::TCPFlag::SYN) == "Set") {
    Process httpProcess;
    try {
      httpProcess = getProcessByName("HTTP");
    } catch (const std::runtime_error &re) {
      qDebug() << "Could not find HTTP Process in Server::receivePackage TCP "
                  "Handshake Package";
    }

    httpProcess.getSocket().setDestinationPort(
        HeaderUtil::getPortAsPort(data, true));

    Package synAckPackage = httpProcess.generateHandShakePackage(
        HeaderUtil::getIPAddressAsIPAddress(data, true), false, false);

    MACAddress routerMAC = this->hostTable().value(
        HeaderUtil::getIPAddressAsIPAddress(data, true));
    Router *router;
    try {
      router = this->getRouterByMACAddress(routerMAC);
    } catch (const CableNotFoundException &cnfe) {
      qDebug() << cnfe.errorMessage()
               << " in Server::receivePackage receiving TCP Handshakepackage";
      return;
    }

    if (router == nullptr) {
      qDebug() << "Router is nullptr in Server::receivePackage";
      return;
    }

    qInfo() << "Server: " << this->networkCard().networkAddress().toString()
            << " sends SYNACK Package to Router: "
            << router->networkCard().physicalAddress().toString();
    router->receivePackage(synAckPackage);
    return;
  }

  if (HeaderUtil::getTCPFlag(data, NetSim::TCPFlag::FIN) == "Set") {
    Process httpProcess;
    try {
      httpProcess = getProcessByName("HTTP");
    } catch (const std::runtime_error &re) {
      qDebug() << "Process HTTP not found in: Server::receivePackage "
                  "connection close";
      return;
    }

    httpProcess.getSocket().setDestinationPort(
        HeaderUtil::getPortAsPort(data, true));

    Package finAckPackage = httpProcess.generateCloseConnectionPackage(
        HeaderUtil::getIPAddressAsIPAddress(data, true), false, false);

    MACAddress routerMAC = this->hostTable().value(
        HeaderUtil::getIPAddressAsIPAddress(data, true));
    Router *router;
    try {
      router = this->getRouterByMACAddress(routerMAC);
    } catch (const CableNotFoundException &cnfe) {
      qDebug()
          << cnfe.errorMessage()
          << " in Server::receivePackage creating the closeConnection Response";
      return;
    }

    if (router == nullptr) {
      qDebug() << "Router is nullptr in Server::receivePackage";
      return;
    }

    qInfo() << "Server: " << this->networkCard().networkAddress().toString()
            << " sends FINACK Package to router: "
            << router->networkCard().physicalAddress().toString();
    router->receivePackage(finAckPackage);
    return;
  }

  if (HeaderUtil::getHTTPIsRequest(data)) {
    Process httpProcess;
    try {
      httpProcess = getProcessByName("HTTP");
    } catch (const std::runtime_error &re) {
      qDebug()
          << "Could not find Process HTTP in: HeaderUtil::getHTTPIsRequest";
      return;
    }

    Package httpResponse;
    if (HeaderUtil::getHTTPAttribute(data, "URI") == "/index.html") {
      httpResponse = httpProcess.generateHTTPResponsePackage(
          HeaderUtil::getIPAddressAsIPAddress(data, true),
          HeaderUtil::getPortAsPort(data, true), 200);
    } else {
      httpResponse = httpProcess.generateHTTPResponsePackage(
          HeaderUtil::getIPAddressAsIPAddress(data, true),
          HeaderUtil::getPortAsPort(data, true), 404);
    }

    MACAddress routerMAC = this->hostTable().value(
        HeaderUtil::getIPAddressAsIPAddress(data, true));
    Router *router;
    try {
      router = this->getRouterByMACAddress(routerMAC);
    } catch (const CableNotFoundException &cnfe) {
      qDebug() << cnfe.errorMessage()
               << " in Server::receivePackage creating HTTP Response";
      return;
    }

    if (router == nullptr) {
      qDebug() << "Router is nullptr in Server::receivePackage";
      return;
    }

    qInfo() << "Server: " << this->networkCard().networkAddress().toString()
            << " sends HTTP Response to router: "
            << router->networkCard().physicalAddress().toString();
    router->receivePackage(httpResponse);
    return;
  }
}
