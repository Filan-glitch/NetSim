#include "tcpclienthandshakestrategy.h"
#include "src/network/cablenotfoundexception.h"
#include "src/network/router.h"
#include "src/protocols/headerutil.h"

using namespace NetSim;

void NetSim::TCPClientHandshakeStrategy::handle(Package package,
                                                Host *host) const {
  MACAddress routerMAC = host->hostTable().value(
      HeaderUtil::getIPAddressAsIPAddress(package, true));
  Router *router;
  try {
    router = host->getRouterByMACAddress(routerMAC);
  } catch (const CableNotFoundException &cnfe) {
    qDebug() << cnfe.errorMessage()
             << " in Client::receivePackage getting the TCP Handshake Package";
    return;
  }

  if (router == nullptr) {
    qDebug() << "Router is nullptr in Client::receivePackage";
    return;
  }

  Process httpProcess;
  try {
    httpProcess = host->getProcessByName("HTTP");
  } catch (const std::runtime_error &re) {
    qDebug() << "Could not find Process HTTP in Client::receivePackage "
                "receiving TCP Handshake Package from Server";
    return;
  }

  qInfo() << "Client: " << host->networkCard().networkAddress().toString()
          << " sends 3. Handshake Package to router: "
          << router->networkCard().physicalAddress().toString();
  router->receivePackage(httpProcess.generateHandShakePackage(
      HeaderUtil::getIPAddressAsIPAddress(package, true), false, true));
}
