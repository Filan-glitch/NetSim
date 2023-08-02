#ifndef ROUTER_H
#define ROUTER_H

#include <QString>
#include <QHash>
#include "src/models/ipaddress.h"
#include "src/network/networkcard.h"

class Router
{
private:
    QHash<QString, IPAddress> domainTable;
    NetworkCard networkCard;
    IPAddress globalIpAddress;
public:
    Router();

    void addDomain(const QString &domain, const IPAddress &ipAddress);
    bool initializeServerConnection();
    void getPackage();
    void forwardPackage();
    IPAddress getGlobalIpAddress() const;
    NetworkCard getNetworkCard() const;
};

#endif // ROUTER_H
