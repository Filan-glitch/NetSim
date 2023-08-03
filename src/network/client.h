#ifndef CLIENT_H
#define CLIENT_H

#include "host.h"

class Client : public Host
{
public:
    Client(const NetworkCard &networkCard);

    Package getHTTPRequest(const QString &url);

    Package getHandShakePackage(const QString &url, bool initiate);


};

#endif // CLIENT_H
