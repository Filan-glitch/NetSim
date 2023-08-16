#ifndef TCPSERVERHANDSHAKESTRATEGY_H
#define TCPSERVERHANDSHAKESTRATEGY_H

#include "ipackagestrategy.h"

//! \file tcphandshakestrategy.h
//! \ingroup NetSimTCPHandshakeStrategy
//! \brief Contains the TCPHandshakeStrategy class definition.

namespace NetSim {

//! \defgroup NetSimTCPHandshakeStrategy TCP Handshake Strategy
//! \brief Provides a strategy for handling TCP handshakes in the network
//! simulation.

/**
 * @class TCPHandshakeStrategy
 * @ingroup NetSimTCPHandshakeStrategy
 * @brief Strategy to handle the TCP handshake process.
 *
 * The TCPHandshakeStrategy class provides a concrete implementation of the
 * IPackageStrategy interface. It defines the logic to initiate or respond to a
 * TCP handshake by sending or acknowledging SYN and SYN-ACK packets.
 */
class TCPServerHandshakeStrategy : public IPackageStrategy {
public:
  /**
   * @brief Default constructor.
   *
   * Establishes a new instance of the TCPHandshakeStrategy.
   */
  TCPServerHandshakeStrategy() = default;

  /**
   * @brief Virtual destructor to ensure correct cleanup for derived classes.
   *
   * Ensures that derived strategy objects related to TCP handshake are properly
   * destroyed.
   */
  virtual ~TCPServerHandshakeStrategy() = default;

  /**
   * @brief Handles the TCP handshake process.
   *
   * @param package The package containing handshake details.
   * @param host The context in which the strategy is invoked.
   *
   * Based on the incoming package details, this method will generate the
   * appropriate handshake packets (e.g., SYN, SYN-ACK) and route them through
   * the network simulation.
   */
  void handle(Package package, Host *host) override;
};

} // namespace NetSim

#endif // TCPSERVERHANDSHAKESTRATEGY_H
