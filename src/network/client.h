#ifndef CLIENT_H
#define CLIENT_H

#include "host.h"

class Client : public Host
{
private:
    QMap<QString, IPAddress> domainTable;

public:
    Client(const NetworkCard &networkCard);
    QMap<QString, IPAddress> getDomainTable() const;


};

#endif // CLIENT_H
