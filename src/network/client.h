#ifndef CLIENT_H
#define CLIENT_H

#include "host.h"

class Client : public Host
{
public:
    Client(const NetworkCard &networkCard);


    IPAddress execDomainResolution(const QString &domain);
    void execHandShake(const IPAddress &address);
    void execHTTPRequest(const IPAddress &address, const QString &uri);
    void execCloseConnection(const IPAddress &address);
    void receivePackage(Package &data) override;
};

#endif // CLIENT_H
