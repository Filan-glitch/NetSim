#ifndef CLIENT_H
#define CLIENT_H

#include "host.h"

class Client : public Host
{
private:

public:
    Client(const NetworkCard &networkCard);

    IPAddress execDomainResolution(const QString &domain);
    void execHandShake(const QString &domain);
    void execHTTPRequest();
    void execCloseConnection();
    void receivePackage(Package &data) override;
};

#endif // CLIENT_H
