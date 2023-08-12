#ifndef DNSSTRATEGY_H
#define DNSSTRATEGY_H

#include "ipackagestrategy.h"

namespace NetSim {

class DNSStrategy : public IPackageStrategy {
public:
  DNSStrategy() = default;
  virtual ~DNSStrategy() = default;
  void handle(Package package, Host *host) override;
};
} // namespace NetSim

#endif // DNSSTRATEGY_H
