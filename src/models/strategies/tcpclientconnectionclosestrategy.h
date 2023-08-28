#ifndef TCPCLIENTCONNECTIONCLOSESTRATEGY_H
#define TCPCLIENTCONNECTIONCLOSESTRATEGY_H

#include "ipackagestrategy.h"

//! \file tcpclientconnectionclosestrategy.h
//! \ingroup NetSimTCPClient
//! \brief Contains the TCPClientConnectionCloseStrategy class definition.

namespace NetSim {

//! \defgroup NetSimTCPClient TCP Client Connection Close Strategy
//! \brief Provides a strategy for handling TCP client connection close
//! packages.

/**
 * @class TCPClientConnectionCloseStrategy
 * @ingroup NetSimTCPClient
 * @brief Implements the client-side TCP connection close strategy.
 *
 * This strategy handles the client-side behavior when attempting to close
 * a TCP connection. It defines how a package should be processed by a client
 * when closing a connection to the server.
 */
class TCPClientConnectionCloseStrategy : public IPackageStrategy {
public:
  /**
   * @brief Default constructor.
   */
  TCPClientConnectionCloseStrategy() = default;

  /**
   * @brief Default destructor.
   */
  virtual ~TCPClientConnectionCloseStrategy() = default;

  /**
   * @brief Handles the package to close the connection.
   *
   * @param package Package to be processed.
   * @param host Client host.
   *
   * This method is responsible for processing the package intended to close
   * the connection. It looks up the router associated with the connection,
   * retrieves the HTTP process from the client's host, and forwards the closing
   * handshake package to the router.
   */
  void handle(Package package, Host *host) const override;
};

} // namespace NetSim

#endif // TCPCLIENTCONNECTIONCLOSESTRATEGY_H
