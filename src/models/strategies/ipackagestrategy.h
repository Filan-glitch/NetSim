#ifndef IPACKAGESTRATEGY_H
#define IPACKAGESTRATEGY_H

#include "src/models/package.h"
#include "src/network/host.h"

namespace NetSim {

class IPackageStrategy {
public:
  IPackageStrategy() = default;
  virtual ~IPackageStrategy() = default;
  virtual void handle(Package package, Host *host) = 0;
};
} // namespace NetSim

#endif // IPACKAGESTRATEGY_H
