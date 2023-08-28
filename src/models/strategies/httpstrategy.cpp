#include "httpstrategy.h"
#include "src/network/cablenotfoundexception.h"
#include "src/network/router.h"
#include "src/protocols/headerutil.h"

using namespace NetSim;

// Strategies overridden handle function
void HTTPStrategy::handle(Package package, Host *host) const {
  Process httpProcess;
  try {
    httpProcess = host->getProcessByName("HTTP");
  } catch (const std::runtime_error &re) {
    qDebug() << "Could not find Process HTTP in: HeaderUtil::getHTTPIsRequest";
    return;
  }

  // Generating the response package
  Package httpResponse;
  if (HeaderUtil::getHTTPAttribute(package, "URI") == "/index.html") {
    httpResponse = httpProcess.generateHTTPResponsePackage(
        HeaderUtil::getIPAddressAsIPAddress(
            package, true), // Old src address to new dst address
        HeaderUtil::getPortAsPort(package, true), // Old port to new port
        200);                                     // Status code 200 for OK
  } else {
    httpResponse = httpProcess.generateHTTPResponsePackage(
        HeaderUtil::getIPAddressAsIPAddress(package, true),
        HeaderUtil::getPortAsPort(package, true),
        404); // Status code 404 for Not Found
  }

  // Establishing connection to router
  MACAddress routerMAC = host->hostTable().value(
      HeaderUtil::getIPAddressAsIPAddress(package, true));
  Router *router;
  try {
    router = host->getRouterByMACAddress(routerMAC);
  } catch (const CableNotFoundException &cnfe) {
    qDebug() << cnfe.errorMessage()
             << " in Server::receivePackage creating HTTP Response";
    return;
  }

  if (router == nullptr) {
    qDebug() << "Router is nullptr in Server::receivePackage";
    return;
  }

  qInfo() << "Server: " << host->networkCard().networkAddress().toString()
          << " sends HTTP Response to router: "
          << router->networkCard().physicalAddress().toString();
  // Sending package to router
  router->receivePackage(httpResponse);
}
