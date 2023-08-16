#ifndef TCPSERVERCONNECTIONCLOSESTRATEGY_H
#define TCPSERVERCONNECTIONCLOSESTRATEGY_H

#include "ipackagestrategy.h"

//! \file tcpconnectionclosestrategy.h
//! \ingroup NetSimTCPConnectionCloseStrategy
//! \brief Contains the TCPConnectionCloseStrategy class definition.

namespace NetSim {

//! \defgroup NetSimTCPConnectionCloseStrategy TCP Connection Close Strategy
//! \brief Provides a strategy for handling TCP connection termination in the
//! network simulation.

/**
 * @class TCPConnectionCloseStrategy
 * @ingroup NetSimTCPConnectionCloseStrategy
 * @brief Strategy to handle the termination of TCP connections.
 *
 * The TCPConnectionCloseStrategy class provides a concrete implementation of
 * the IPackageStrategy interface. It defines the logic to gracefully close a
 * TCP connection by sending the appropriate termination packets.
 */
class TCPServerConnectionCloseStrategy : public IPackageStrategy {
public:
  /**
   * @brief Default constructor.
   *
   * Establishes a new instance of the TCPConnectionCloseStrategy.
   */
    TCPServerConnectionCloseStrategy() = default;

  /**
   * @brief Virtual destructor to ensure correct cleanup for derived classes.
   *
   * Ensures that derived strategy objects related to TCP connection termination
   * are properly destroyed.
   */
    virtual ~TCPServerConnectionCloseStrategy() = default;

  /**
   * @brief Handles the TCP connection termination process.
   *
   * @param package The package containing connection termination details.
   * @param host The context in which the strategy is invoked.
   *
   * Based on the incoming package details, this method will generate the
   * appropriate TCP termination packets (e.g., FIN, FIN-ACK) and route them
   * through the network simulation.
   */
  void handle(Package package, Host *host) override;
};

} // namespace NetSim

#endif // TCPSERVERCONNECTIONCLOSESTRATEGY_H
