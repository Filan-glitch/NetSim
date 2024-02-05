#ifndef DNSSTRATEGY_H
#define DNSSTRATEGY_H

#include "ipackagestrategy.h"

//! \file dnsstrategy.h
//! \ingroup NetSimDNSStrategy
//! \brief Contains the DNSStrategy class definition.

namespace NetSim {

//! \defgroup NetSimDNSStrategy DNS Strategy
//! \brief Provides a strategy for handling DNS packages

/**
 * @class DNSStrategy
 * @ingroup NetSimDNSStrategy
 * @brief Strategy class for handling DNS packages.
 *
 * The DNSStrategy class provides the specific behavior for handling
 * DNS packages within the networking simulation. This strategy class
 * allows for decoupling the DNS package handling logic from the main
 * host logic. Inherits from the IPackageStrategy interface.
 */
class DNSStrategy : public IPackageStrategy {
public:
  /**
   * @brief Default constructor.
   *
   * Initializes a new instance of the DNSStrategy class.
   */
  DNSStrategy() = default;

  /**
   * @brief Virtual destructor for cleanup and to allow for polymorphism.
   *
   * Ensures proper cleanup of derived strategy objects and supports dynamic
   * dispatch.
   */
  virtual ~DNSStrategy() = default;

  /**
   * @brief Handles the DNS package.
   *
   * @param package The DNS package to handle.
   * @param host The host context from which the strategy is being invoked.
   *
   * This method provides the specific behavior for handling DNS packages.
   * It processes the DNS request, generates a response, and forwards
   * it to the appropriate router.
   */
  void handle(Package package, Host *host) const override;
};
} // namespace NetSim

#endif // DNSSTRATEGY_H
