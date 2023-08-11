#include "client.h"
#include "cablenotfoundexception.h"
#include "src/network/router.h"
#include "src/protocols/headerutil.h"
#include "src/protocols/tcp.h"

Client::Client(const NetworkCard &networkCard) : Host(networkCard) {}

void Client::execDomainResolution(const QString &domain) {
  qInfo() << "Executing: Client::execDomainResolution"
          << " Client: " << this->networkCard().networkAddress().toString();

  if (domainTable().contains(domain)) {
    qInfo() << "Client: " << this->networkCard().networkAddress().toString()
            << " already has IPAddress to Domain: " << domain;
    return;
  }

  Process dnsProcess;
  try {
    dnsProcess = getProcessByName("DNS");
  } catch (const std::runtime_error &re) {
    qDebug() << "Could not find Procces DNS ind Client::execDomainResolution";
    return;
  }

  Package dnsRequest = dnsProcess.generateDNSRequestPackage(domain);

  MACAddress routerMAC = this->hostTable().value(
      this->domainTable().value(QString("dns.beispiel.de")));
  Router *router;
  try {
    router = this->getRouterByMACAddress(routerMAC);
  } catch (const CableNotFoundException &cnfe) {
    qDebug() << cnfe.errorMessage() << " in Client::execDomainResolution";
    return;
  }

  qInfo() << "Client: " << this->networkCard().networkAddress().toString()
          << " sends DNSRequest to Router: "
          << router->networkCard().physicalAddress().toString();
  router->receivePackage(dnsRequest);
}

void Client::execHandShake(const IPAddress &address) {
  qInfo() << "Executing: Client::execHandShake"
          << " Client: " << this->networkCard().networkAddress().toString();

  MACAddress routerMAC = this->hostTable().value(address);
  Router *router;
  try {
    router = this->getRouterByMACAddress(routerMAC);
  } catch (const CableNotFoundException &cnfe) {
    qDebug() << cnfe.errorMessage() << " in Client::execHandShake";
    return;
  }

  if (router == nullptr) {
    qDebug() << "Router is nullptr in Client::execHandShake";
    return;
  }

  Process httpProcess;
  try {
    httpProcess = getProcessByName("HTTP");
  } catch (const std::runtime_error &re) {
    qDebug() << "Could not find Process HTTP in Client::execHandShake";
    return;
  }

  qInfo() << "Client: " << this->networkCard().networkAddress().toString()
          << "sends TCP Handshake Package to Router: "
          << router->networkCard().physicalAddress().toString();
  Package package = httpProcess.generateHandShakePackage(address, true, true);
  router->receivePackage(package);
}

void Client::execHTTPRequest(const IPAddress &address, const QString &uri) {
  qInfo() << "Executing: Client::execHTTPRequest"
          << " Client: " << this->networkCard().networkAddress().toString();

  MACAddress routerMAC = this->hostTable().value(address);
  Router *router;
  try {
    router = this->getRouterByMACAddress(routerMAC);
  } catch (const CableNotFoundException &cnfe) {
    qDebug() << cnfe.errorMessage() << " in Client::execHTTPRequest";
    return;
  }

  if (router == nullptr) {
    qDebug() << "Router is nullptr in Client::execHTTPRequest";
    return;
  }

  Process httpProcess;
  try {
    httpProcess = getProcessByName("HTTP");
  } catch (const std::runtime_error &re) {
    qDebug() << "Could not find Process HTTP in Client::execHTTPRequest";
    return;
  }

  qInfo() << "Client: " << this->networkCard().networkAddress().toString()
          << " sends HTTPRequest Package to Router: "
          << router->networkCard().physicalAddress().toString();
  router->receivePackage(httpProcess.generateHTTPRequestPackage(uri, address));
}

void Client::execCloseConnection(const IPAddress &address) {
  qInfo() << "Executing: Client::execCloseConnection"
          << " Client: " << this->networkCard().networkAddress().toString();

  MACAddress routerMAC = this->hostTable().value(address);
  Router *router;
  try {
    router = this->getRouterByMACAddress(routerMAC);
  } catch (const CableNotFoundException &cnfe) {
    qDebug() << cnfe.errorMessage() << " in Client::execCloseConnection";
    return;
  }

  if (router == nullptr) {
    qDebug() << "Router is nullptr in Client::execHandShake";
    return;
  }

  Process httpProcess;
  try {
    httpProcess = getProcessByName("HTTP");
  } catch (const std::runtime_error &re) {
    qDebug() << "Could not find Process HTTP in Client::execCloseConnection";
    return;
  }

  qInfo() << "Client sends close connection Package to router: "
          << router->networkCard().physicalAddress().toString();
  router->receivePackage(
      httpProcess.generateCloseConnectionPackage(address, true, true));
}

void Client::receivePackage(Package data) {
  packages()->addPackage(data);
  qInfo() << "Client: " << this->networkCard().networkAddress().toString()
          << " received Package: " << data.info()
          << " Client: " << this->networkCard().networkAddress().toString();

  // Receives a DNS Response Package from Server
  if (HeaderUtil::getTopProtocol(data) == NetSim::HeaderType::DNS) {
    for (auto i = 0; i < HeaderUtil::getDNSAnswerRRs(data).toInt(); i++) {
      addDomain(HeaderUtil::getDNSAnswer(data, i, NetSim::RRAttribute::NAME),
                HeaderUtil::getDNSAnswerIPAddress(data, i));
    }
    return;
  }

  if (HeaderUtil::getTCPFlag(data, NetSim::TCPFlag::SYN) == "Set" &&
      HeaderUtil::getTCPFlag(data, NetSim::TCPFlag::ACK) == "Set") {
    MACAddress routerMAC = this->hostTable().value(
        HeaderUtil::getIPAddressAsIPAddress(data, true));
    Router *router;
    try {
      router = this->getRouterByMACAddress(routerMAC);
    } catch (const CableNotFoundException &cnfe) {
      qDebug()
          << cnfe.errorMessage()
          << " in Client::receivePackage getting the TCP Handshake Package";
      return;
    }

    if (router == nullptr) {
      qDebug() << "Router is nullptr in Client::receivePackage";
      return;
    }

    Process httpProcess;
    try {
      httpProcess = getProcessByName("HTTP");
    } catch (const std::runtime_error &re) {
      qDebug() << "Could not find Process HTTP in Client::receivePackage "
                  "receiving TCP Handshake Package from Server";
      return;
    }

    qInfo() << "Client: " << this->networkCard().networkAddress().toString()
            << " sends 3. Handshake Package to router: "
            << router->networkCard().physicalAddress().toString();
    router->receivePackage(httpProcess.generateHandShakePackage(
        HeaderUtil::getIPAddressAsIPAddress(data, true), false, true));
  }

  if (HeaderUtil::getTCPFlag(data, NetSim::TCPFlag::FIN) == "Set" &&
      HeaderUtil::getTCPFlag(data, NetSim::TCPFlag::ACK) == "Set") {
    MACAddress routerMAC = this->hostTable().value(
        HeaderUtil::getIPAddressAsIPAddress(data, true));
    Router *router;
    try {
      router = this->getRouterByMACAddress(routerMAC);
    } catch (const CableNotFoundException &cnfe) {
      qDebug() << cnfe.errorMessage()
               << " in Client::receivePackage receiving the closing Package "
                  "from Server";
      return;
    }
    if (router == nullptr) {
      qDebug() << "Router is nullptr in Client::receivePackage";
      return;
    }

    Process httpProcess;
    try {
      httpProcess = getProcessByName("HTTP");
    } catch (const std::runtime_error &re) {
      qDebug() << "Could not find Process HTTP in Client::receivePackage "
                  "receiving a closing package from Server";
      return;
    }
    qInfo() << "Client: " << this->networkCard().networkAddress().toString()
            << " sends 3. Handshake Package to router: "
            << router->networkCard().physicalAddress().toString();
    router->receivePackage(httpProcess.generateCloseConnectionPackage(
        HeaderUtil::getIPAddressAsIPAddress(data, true), false, true));
  }
}
