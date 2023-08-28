#ifndef CLIENT_H
#define CLIENT_H

#include "host.h"

//! \file client.h
//! \ingroup NetSimClient
//! \brief Contains the Client class definition

namespace NetSim {

//! \defgroup NetSimClient Client
//! \brief Simulates a client in a network

/**
 * @class Client
 * @ingroup NetSimClient
 * @brief Represents a client in the network simulation.
 *
 * The Client class is responsible for initiating network requests such as DNS
 * resolution, establishing TCP handshakes, making HTTP requests, and closing
 * connections.
 */
class Client : public Host {
public:
  //! @brief Default constructor.
  Client() = default;

  /**
   * @brief Constructs a client with the provided network card.
   *
   * @param networkCard Network interface card of the client.
   */
  Client(const NetworkCard &networkCard);

  /**
   * @brief Initiates a domain name resolution.
   *
   * @param domain Domain name to be resolved.
   */
  void execDomainResolution(const QString &domain);

  /**
   * @brief Initiates a TCP handshake to the specified IP address.
   *
   * @param address IP address to establish a connection.
   */
  void execHandShake(const IPAddress &address);

  /**
   * @brief Sends an HTTP request to the specified IP address and URI.
   *
   * @param address IP address of the server to send the request.
   * @param uri Requested Uniform Resource Identifier.
   */
  void execHTTPRequest(const IPAddress &address, const QString &uri);

  /**
   * @brief Closes the connection to the specified IP address.
   *
   * @param address IP address to close the connection.
   */
  void execCloseConnection(const IPAddress &address);

  /**
   * @brief Receives a package and processes based on its type.
   *
   * The client can receive and process DNS Response, TCP Handshake, and TCP
   * closing packages.
   *
   * @param data Package data received by the client.
   */
  void receivePackage(Package data) override;
};
} // namespace NetSim

#endif // CLIENT_H
