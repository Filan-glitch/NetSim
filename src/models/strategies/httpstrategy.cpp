#include "httpstrategy.h"
#include "src/network/cablenotfoundexception.h"
#include "src/network/router.h"
#include "src/protocols/headerutil.h"

using namespace NetSim;

HTTPStrategy::~HTTPStrategy() {}

void HTTPStrategy::handle(Package package, Host *host) {
  Process httpProcess;
  try {
    httpProcess = host->getProcessByName("HTTP");
  } catch (const std::runtime_error &re) {
    qDebug() << "Could not find Process HTTP in: HeaderUtil::getHTTPIsRequest";
    return;
  }

  Package httpResponse;
  if (HeaderUtil::getHTTPAttribute(package, "URI") == "/index.html") {
    httpResponse = httpProcess.generateHTTPResponsePackage(
        HeaderUtil::getIPAddressAsIPAddress(package, true),
        HeaderUtil::getPortAsPort(package, true), 200);
  } else {
    httpResponse = httpProcess.generateHTTPResponsePackage(
        HeaderUtil::getIPAddressAsIPAddress(package, true),
        HeaderUtil::getPortAsPort(package, true), 404);
  }

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
  router->receivePackage(httpResponse);
}
