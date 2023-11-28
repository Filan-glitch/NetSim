#include "tcpclientconnectionclosestrategy.h"
#include "src/network/cablenotfoundexception.h"
#include "src/network/router.h"
#include "src/network/packageutil.h"

using namespace NetSim;

// Strategies overridden handle function
void NetSim::TCPClientConnectionCloseStrategy::handle(Package package,
                                                      Host *host) const {
  Process httpProcess;
  try {
    httpProcess = host->getProcessByName("HTTP");
  } catch (const std::runtime_error &re) {
    qDebug() << "Could not find Process HTTP in Client::receivePackage "
                "receiving a closing package from Server";
    return;
  }

  // Generating the response package
  Package httpResponse = httpProcess.generateCloseConnectionPackage(
      HeaderUtil::getIPAddressAsIPAddress(package, true), false, true);

  // Establishing connection to router
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

  qInfo() << "Client: " << host->networkCard().networkAddress().toString()
          << " sends 3. Handshake Package to router: "
          << router->networkCard().physicalAddress().toString();
  // Sending the package to router
  router->receivePackage(httpResponse);
}
