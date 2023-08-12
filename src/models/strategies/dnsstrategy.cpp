#include "dnsstrategy.h"
#include "src/network/cablenotfoundexception.h"
#include "src/network/router.h"
#include "src/protocols/headerutil.h"

using namespace NetSim;

void NetSim::DNSStrategy::handle(Package package, Host *host) {
  Process dnsProcess;
  try {
    dnsProcess = host->getProcessByName("DNS");
  } catch (const std::runtime_error &re) {
    qDebug() << "Could not find Process DNS in Server::receivePackage DNS "
                "Request Package";
    return;
  }

  Package dnsResponse = dnsProcess.generateDNSResponsePackage(
      HeaderUtil::getIPAddressAsIPAddress(package, true),
      HeaderUtil::getDNSQuery(package, 0, RRAttribute::NAME),
      HeaderUtil::getPortAsPort(package, true));

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
  router->receivePackage(dnsResponse);
}
