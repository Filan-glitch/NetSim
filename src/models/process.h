#ifndef PROCESS_H
#define PROCESS_H

#include "ipaddress.h"
#include "src/network/socket.h"
#include <QString>

namespace NetSim {
class Process;
}

class Host;

class Process {
public:
  Process(){};

  Process(const Port &destinationPort, const QString &name);

  Socket &getSocket();

  void openSocket(const Port &destinationPort);

  Package generateHTTPRequestPackage(const QString &uri,
                                     const IPAddress &destination);

  Package generateHTTPResponsePackage(const IPAddress &destination,
                                      const Port &destPort,
                                      const int &messageCode);

  Package generateHandShakePackage(const IPAddress &address, bool initiate,
                                   bool client);

  Package generateCloseConnectionPackage(const IPAddress &address,
                                         bool initiate, bool client);

  Package generateDNSRequestPackage(const QString &domain);

  Package generateDNSResponsePackage(const IPAddress &destination,
                                     const QString &domain,
                                     const Port &destPort);

  QString name() const;

  void setHost(Host *host);

  QString toString() const;

private:
  QString m_name;

  Socket m_socket;

  Host *m_host;
};

#endif // PROCESS_H
