#ifndef ROUTER_H
#define ROUTER_H

#include <QString>
#include <QHash>
#include "src/models/ipaddress.h"

class Router
{
private:
    QHash<QString, IPAddress> domainTable;
public:
    Router()
    {}


    bool initializeServerConnection();
    void getPackage();
    void forwardPackage();
};

#endif // ROUTER_H
