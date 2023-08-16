#include "tcpclientconnectionclosestrategy.h"
#include "src/network/cablenotfoundexception.h"
#include "src/network/router.h"
#include "src/protocols/headerutil.h"

using namespace NetSim;

void NetSim::TCPClientConnectionCloseStrategy::handle(Package package,
                                                      Host *host) {
  MACAddress routerMAC = host->hostTable().value(
      HeaderUtil::getIPAddressAsIPAddress(package, true));
  Router *router;
  try {
    router = host->getRouterByMACAddress(routerMAC);
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
    httpProcess = host->getProcessByName("HTTP");
  } catch (const std::runtime_error &re) {
    qDebug() << "Could not find Process HTTP in Client::receivePackage "
                "receiving a closing package from Server";
    return;
  }
  qInfo() << "Client: " << host->networkCard().networkAddress().toString()
          << " sends 3. Handshake Package to router: "
          << router->networkCard().physicalAddress().toString();
  router->receivePackage(httpProcess.generateCloseConnectionPackage(
      HeaderUtil::getIPAddressAsIPAddress(package, true), false, true));
}