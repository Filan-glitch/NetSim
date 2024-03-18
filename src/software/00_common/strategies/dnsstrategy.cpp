#include "dnsstrategy.h"
#include "src/hardware/cablenotfoundexception.h"
#include "src/hardware/router.h"
#include "src/software/00_common/headerutil.h"

using namespace NetSim;

// Strategies overridden handle function
void NetSim::DNSStrategy::handle(Package package, Host *host) const {
  Process dnsProcess;
  try {
    dnsProcess = host->getProcessByName("DNS");
  } catch (const std::runtime_error &re) {
    qDebug() << "Could not find Process DNS in Server::receivePackage DNS "
                "Request Package";
    return;
  }

  // Generating the response package
  Package dnsResponse = dnsProcess.generateDNSResponsePackage(
      HeaderUtil::getIPAddressAsIPAddress(
          package, true), // Old src address to new dst address
      HeaderUtil::getDNSQuery(package, 0, RRAttribute::NAME), // Queried domain
      HeaderUtil::getPortAsPort(package, true)); // Old src port to new dst port

  // Establishing connection to router
  MACAddress routerMAC = host->hostTable().value(
      HeaderUtil::getIPAddressAsIPAddress(package, true));
  Router *router;
  try {
    router = host->getRouterByMACAddress(routerMAC);
  } catch (const CableNotFoundException &cnfe) {
    qDebug() << cnfe.errorMessage()
             << " in Server::receivePackage creating DNS Response";
    return;
  }

  if (router == nullptr) {
    qDebug() << "Router is nullptr in Server::receivePackage";
    return;
  }

  qInfo() << "Server: " << host->networkCard().networkAddress().toString()
          << " sends DNSResponse to Router: "
          << router->networkCard().physicalAddress().toString();
  // Sending package to router
  router->receivePackage(dnsResponse);
}
