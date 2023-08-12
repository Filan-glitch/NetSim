#ifndef HTTPSTRATEGY_H
#define HTTPSTRATEGY_H

#include "ipackagestrategy.h"

namespace NetSim {

class HTTPStrategy : public IPackageStrategy {
public:
  HTTPStrategy() = default;
  virtual ~HTTPStrategy() = default;
  void handle(Package package, Host *host) override;
};
} // namespace NetSim

#endif // HTTPSTRATEGY_H
