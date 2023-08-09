#ifndef PROCESS_H
#define PROCESS_H

#include "src/network/socket.h"
#include "ipaddress.h"

#include <QString>

class Host;

class Process
{
public:
    Process(){};

    Process(Host* host, const Port &destinationPort);

    Socket getSocket();

    void openSocket(const Port &destinationPort);

    Package getHTTPRequest(const QString &uri,const IPAddress &destination);

    Package getHTTPResponse(const IPAddress &destination);

    Package getHandShakePackage(const IPAddress &address, bool initiate, bool client);

    Package getCloseConnectionPackage(const IPAddress &address, bool initiate, bool client);

private:
    Socket socket;
    Host* host;
};

#endif // PROCESS_H
