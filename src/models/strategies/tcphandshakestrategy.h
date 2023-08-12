#ifndef TCPHANDSHAKESTRATEGY_H
#define TCPHANDSHAKESTRATEGY_H

#include "ipackagestrategy.h"

namespace NetSim {

class TCPHandshakeStrategy : public IPackageStrategy {
public:
  TCPHandshakeStrategy() = default;
  virtual ~TCPHandshakeStrategy() = default;
  void handle(Package package, Host *host) override;
};
} // namespace NetSim

#endif // TCPHANDSHAKESTRATEGY_H
