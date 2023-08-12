#ifndef TCPCONNECTIONCLOSESTRATEGY_H
#define TCPCONNECTIONCLOSESTRATEGY_H

#include "ipackagestrategy.h"

namespace NetSim {

class TCPConnectionCloseStrategy : public IPackageStrategy {
public:
  TCPConnectionCloseStrategy() = default;
  virtual ~TCPConnectionCloseStrategy() = default;
  void handle(Package package, Host *host) override;
};
} // namespace NetSim

#endif // TCPCONNECTIONCLOSESTRATEGY_H
