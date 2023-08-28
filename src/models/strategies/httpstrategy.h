#ifndef HTTPSTRATEGY_H
#define HTTPSTRATEGY_H

#include "ipackagestrategy.h"

//! \file httpstrategy.h
//! \ingroup NetSimHTTPStrategy
//! \brief Contains the HTTPStrategy class definition.

namespace NetSim {

//! \defgroup NetSimHTTPStrategy HTTP Strategy
//! \brief Provides a strategy for handling HTTP packages

/**
 * @class HTTPStrategy
 * @ingroup NetSimHTTPStrategy
 * @brief Strategy class for handling HTTP packages.
 *
 * The HTTPStrategy class offers specific behavior for processing
 * HTTP packages within the networking simulation environment. By employing
 * this strategy class, the HTTP package handling logic can be decoupled
 * from the primary host procedures. This class derives from the
 * IPackageStrategy interface.
 */
class HTTPStrategy : public IPackageStrategy {
public:
  /**
   * @brief Default constructor.
   *
   * Establishes a new instance of the HTTPStrategy class.
   */
  HTTPStrategy() = default;

  /**
   * @brief Virtual destructor to ensure correct cleanup and facilitate
   * polymorphism.
   *
   * Enables proper cleanup of derived strategy objects and promotes dynamic
   * dispatch.
   */
  virtual ~HTTPStrategy() = default;

  /**
   * @brief Manages the HTTP package.
   *
   * @param package The HTTP package in consideration.
   * @param host The host context where the strategy is invoked.
   *
   * This function embodies the specific behavior necessary for handling
   * HTTP packages. It interprets the HTTP request, crafts a corresponding
   * response, and dispatches it to the appropriate router.
   */
  void handle(Package package, Host *host) const override;
};
} // namespace NetSim

#endif // HTTPSTRATEGY_H
