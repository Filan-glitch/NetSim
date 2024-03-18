#include "client.h"
#include "cablenotfoundexception.h"
#include "src/software/00_common/strategies/ipackagestrategy.h"
#include "src/software/00_common/strategies/tcpclientconnectionclosestrategy.h"
#include "src/software/00_common/strategies/tcpclienthandshakestrategy.h"
#include "src/hardware/router.h"
#include "src/software/00_common/headerutil.h"
#include "src/software/02_transport_layer/tcp.h"

using namespace NetSim;

Client::Client(const NetworkCard &networkCard) : Host(networkCard) {}

void Client::execDomainResolution(const QString &domain) {
  qInfo() << "Executing: Client::execDomainResolution"
          << " Client: " << this->networkCard().networkAddress().toString();

  // Skipping if client already has domain in the cache
  if (domainTable().contains(domain)) {
    qInfo() << "Client: " << this->networkCard().networkAddress().toString()
            << " already has domain: " << domain;
    return;
  }

  Process dnsProcess;
  try {
    dnsProcess = getProcessByName("DNS");
  } catch (const std::runtime_error &re) {
    qDebug() << "Could not find Procces DNS in Client::execDomainResolution";
    return;
  }

  // Generating DNS request package
  Package dnsRequest = dnsProcess.generateDNSRequestPackage(domain);

  MACAddress routerMAC = this->hostTable().value(
      // Currently using the standard dns server domain
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

  // Using the strategy pattern for handling different types of packages
  // Extendable for new protocols
  IPackageStrategy *strategy = nullptr;

  // Receives a DNS Response Package from Server
  if (HeaderUtil::getTopProtocol(data) == DNS) {
    for (auto i = 0; i < HeaderUtil::getDNSAnswerRRs(data).toInt(); i++) {
      addDomain(HeaderUtil::getDNSAnswer(data, i, RRAttribute::NAME),
                HeaderUtil::getDNSAnswerIPAddress(data, i));
    }
    return;
  }
  // Receives a [SYN, ACK] Package from Server
  if (HeaderUtil::getTCPFlag(data, TCPFlag::SYN) == "Set" &&
      HeaderUtil::getTCPFlag(data, TCPFlag::ACK) == "Set") {
    strategy = new TCPClientHandshakeStrategy();
  }
  // Receives a [FIN, ACK] Package from Server
  if (HeaderUtil::getTCPFlag(data, TCPFlag::FIN) == "Set" &&
      HeaderUtil::getTCPFlag(data, TCPFlag::ACK) == "Set") {
    strategy = new TCPClientConnectionCloseStrategy();
  }

  if (strategy) {
    strategy->handle(data, this);
    delete strategy;
  } else {
    qDebug() << "Package has unknown format and cannot be processed.";
  }
}
