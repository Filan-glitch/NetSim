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

    Process(const Port &destinationPort, const QString &name);

    Socket& getSocket();

    void openSocket(const Port &destinationPort);

    Package getHTTPRequest(const QString &uri,const IPAddress &destination);

    Package getHTTPResponse(const IPAddress &destination, const Port &destPort, const int &messageCode);

    Package getHandShakePackage(const IPAddress &address, bool initiate, bool client);

    Package getCloseConnectionPackage(const IPAddress &address, bool initiate, bool client);

    Package getDNSRequest(const QString& domain);

    Package getDNSResponse(const IPAddress& destination, const QString& domain, const Port& destPort);

    QString getName() const;

    void setHost(Host* host);

    QString toString() const;

private:
    QString name;

    Socket socket;

    Host* host;
};

#endif // PROCESS_H
