#ifndef ROUTER_H
#define ROUTER_H

#include <QString>
#include <QStack>
#include <QHash>
#include "host.h"
#include "src/models/ipaddress.h"
#include "src/network/networkcard.h"

class Host;

class Router
{
private:
    map<QString, IPAddress> domainTable;
    map<MACAddress, Router*> routerCable;
    map<MACAddress, Host*> hostCable;
    NetworkCard networkCard;
    IPAddress globalIpAddress;
    QStack<Package> cachePackage;
public:
    Router();

    void addDomain(const QString &domain, const IPAddress &ipAddress);
    bool initializeServerConnection();
    void receivePackage(const Package& data);
    void sendPackageToRouter(MACAddress destinationAddress);
    void sendPackageToHost(MACAddress destinationAddress);
    IPAddress getGlobalIpAddress() const;
    NetworkCard getNetworkCard() const;
};

#endif // ROUTER_H
