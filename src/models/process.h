#ifndef PROCESS_H
#define PROCESS_H

#include "src/network/socket.h"
#include "ipaddress.h"

#include <QString>

class Host;

class Process
{
public:
    Process();

    void openSocket(const Port &sourcePort);

    Package getHTTPRequest(const QString &url);

    //TODO IMPLEMENT
    Package getHTTPResponse(IPAddress destination);

    //TODO SERVER SIDE
    Package getHandShakePackage(const QString &url, bool initiate, bool client);

private:
    Socket socket;
    Host* host;
};

#endif // PROCESS_H
