#ifndef IPACKAGESTRATEGY_H
#define IPACKAGESTRATEGY_H

#include "src/software/00_common/package.h"
#include "src/hardware/host.h"

//! \file ipackagestrategy.h
//! \ingroup NetSimIPackageStrategy
//! \brief Contains the IPackageStrategy interface definition.

namespace NetSim {

//! \defgroup NetSimIPackageStrategy IPackage Strategy
//! \brief Provides an interface for handling different package strategies.

/**
 * @class IPackageStrategy
 * @ingroup NetSimIPackageStrategy
 * @brief Interface for defining strategies to handle packages.
 *
 * The IPackageStrategy class establishes a contract for all package handling
 * strategy implementations. Classes implementing this interface must provide
 * a concrete implementation for the `handle` method, thus defining their
 * custom logic for processing packages within the networking simulation
 * environment.
 */
class IPackageStrategy {
public:
  /**
   * @brief Default constructor.
   *
   * Establishes a new instance of the IPackageStrategy interface.
   */
  IPackageStrategy() = default;

  /**
   * @brief Virtual destructor to ensure correct cleanup for derived classes.
   *
   * Ensures that derived strategy objects are properly destroyed and promotes
   * dynamic dispatch.
   */
  virtual ~IPackageStrategy() = default;

  /**
   * @brief Abstract method for handling packages.
   *
   * @param package The package to be handled.
   * @param host The context where the strategy will be invoked.
   *
   * Classes implementing this interface must provide a concrete method
   * to define how the given package is to be processed within the provided host
   * context.
   */
  virtual void handle(Package package, Host *host) const = 0;
};
} // namespace NetSim

#endif // IPACKAGESTRATEGY_H
