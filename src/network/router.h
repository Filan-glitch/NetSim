#ifndef ROUTER_H
#define ROUTER_H

#include <QString>
#include <QHash>
#include "../models/ipaddress.h"

class Router
{
private:
    QHash<QString, IPAddress> domainTable;
public:
    Router(const QHash<QString, IPAddress> &domainTable);

    bool initializeServerConnection();
    void getPackage();
    void forwardPackage();
};

#endif // ROUTER_H
