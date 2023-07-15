#ifndef ROUTER_H
#define ROUTER_H

#include <QString>
#include <QHash>
#include "../protocols/ipaddress.h"

class Router
{
private:
    QHash<QString, IPAddress> domainTable;
public:
    Router();
};

#endif // ROUTER_H
