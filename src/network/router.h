#ifndef ROUTER_H
#define ROUTER_H

#include <QString>
#include <QHash>

class Router
{
private:
    QHash<QString, qint32> domainTable;
public:
    Router();
};

#endif // ROUTER_H
