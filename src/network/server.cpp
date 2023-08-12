#include "server.h"
#include "src/models/strategies/dnsstrategy.h"
#include "src/models/strategies/httpstrategy.h"
#include "src/models/strategies/ipackagestrategy.h"
#include "src/models/strategies/tcpconnectionclosestrategy.h"
#include "src/models/strategies/tcphandshakestrategy.h"
#include "src/protocols/headerutil.h"

using namespace NetSim;

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

  IPackageStrategy *strategy = nullptr;

  if (HeaderUtil::getTopProtocol(data) == HeaderType::DNS) {
    strategy = new DNSStrategy();
  } else if (HeaderUtil::getHTTPIsRequest(data)) {
    strategy = new HTTPStrategy();
  } else if (HeaderUtil::getTCPFlag(data, TCPFlag::SYN) == "Set") {
    strategy = new TCPHandshakeStrategy();
  } else if (HeaderUtil::getTCPFlag(data, TCPFlag::FIN) == "Set") {
    strategy = new TCPConnectionCloseStrategy();
  }

  if (strategy) {
    strategy->handle(data, this);
    delete strategy;
  } else {
    qDebug() << "Package has unknown format and cannot be processed.";
  }
}
