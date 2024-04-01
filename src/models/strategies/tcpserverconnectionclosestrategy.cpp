#include "tcpserverconnectionclosestrategy.h"
#include "src/network/cablenotfoundexception.h"
#include "src/network/router.h"
#include "src/utils/packageutil.h"

using namespace NetSim;

void TCPServerConnectionCloseStrategy::handle(Package package,
                                              Host *host) const {
  Process httpProcess;
  try {
    httpProcess = host->getProcessByName("HTTP");
  } catch (const std::runtime_error &re) {
    qDebug() << "Process HTTP not found in: Server::receivePackage "
                "connection close";
    return;
  }

  httpProcess.socket().setDestinationPort(
      PackageUtil::getPortAsPort(package, true));

  Package finAckPackage = httpProcess.generateCloseConnectionPackage(
      PackageUtil::getIPAddressAsIPAddress(package, true), false, false);

  MACAddress routerMAC = host->hostTable().value(
      PackageUtil::getIPAddressAsIPAddress(package, true));
  Router *router;
  try {
    router = host->getRouterByMACAddress(routerMAC);
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

  qInfo() << "Server: " << host->networkCard().networkAddress().toString()
          << " sends FINACK Package to router: "
          << router->networkCard().physicalAddress().toString();
  router->receivePackage(finAckPackage);
}
