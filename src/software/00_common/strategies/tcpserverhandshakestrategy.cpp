#include "tcpserverhandshakestrategy.h"
#include "src/hardware/cablenotfoundexception.h"
#include "src/hardware/router.h"
#include "src/software/00_common/headerutil.h"

using namespace NetSim;

void TCPServerHandshakeStrategy::handle(Package package, Host *host) const {
  Process httpProcess;
  try {
    httpProcess = host->getProcessByName("HTTP");
  } catch (const std::runtime_error &re) {
    qDebug() << "Could not find HTTP Process in Server::receivePackage TCP "
                "Handshake Package";
  }

  httpProcess.socket().setDestinationPort(
      HeaderUtil::getPortAsPort(package, true));

  Package synAckPackage = httpProcess.generateHandShakePackage(
      HeaderUtil::getIPAddressAsIPAddress(package, true), false, false);

  MACAddress routerMAC = host->hostTable().value(
      HeaderUtil::getIPAddressAsIPAddress(package, true));
  Router *router;
  try {
    router = host->getRouterByMACAddress(routerMAC);
  } catch (const CableNotFoundException &cnfe) {
    qDebug() << cnfe.errorMessage()
             << " in Server::receivePackage receiving TCP Handshakepackage";
    return;
  }

  if (router == nullptr) {
    qDebug() << "Router is nullptr in Server::receivePackage";
    return;
  }

  qInfo() << "Server: " << host->networkCard().networkAddress().toString()
          << " sends SYNACK Package to Router: "
          << router->networkCard().physicalAddress().toString();
  router->receivePackage(synAckPackage);
}
