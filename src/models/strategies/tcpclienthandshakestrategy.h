#ifndef TCPCLIENTHANDSHAKESTRATEGY_H
#define TCPCLIENTHANDSHAKESTRATEGY_H

#include "ipackagestrategy.h"

//! \file tcpclienthandshakestrategy.h
//! \ingroup NetSimTCPClient
//! \brief Contains the TCPClientHandshakeStrategy class definition.

namespace NetSim {

//! \defgroup NetSimTCPClient TCP Client Handshake Strategy
//! \brief Provides a strategy for handling TCP client handshake packages.

/**
 * @class TCPClientHandshakeStrategy
 * @ingroup NetSimTCPClient
 * @brief Implements the client-side TCP handshake strategy.
 *
 * This strategy handles the client-side behavior during the initiation of
 * a TCP connection. It defines how a package should be processed by a client
 * when attempting to establish a connection to a server.
 */
class TCPClientHandshakeStrategy : public IPackageStrategy {
public:
  /**
   * @brief Default constructor.
   */
  TCPClientHandshakeStrategy() = default;

  /**
   * @brief Default destructor.
   */
  virtual ~TCPClientHandshakeStrategy() = default;

  /**
   * @brief Handles the package during the handshake process.
   *
   * @param package Package to be processed.
   * @param host Client host.
   *
   * This method is responsible for processing the package intended to initiate
   * the handshake. It retrieves the MAC address of the router associated with
   * the connection, fetches the HTTP process from the client's host, and then
   * sends the handshake package to the router.
   */
  void handle(Package package, Host *host) const override;
};

} // namespace NetSim

#endif // TCPCLIENTHANDSHAKESTRATEGY_H
