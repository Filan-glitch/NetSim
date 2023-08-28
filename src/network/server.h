#ifndef SERVER_H
#define SERVER_H

#include "host.h"

//! \file server.h
//! \ingroup NetSimServer
//! \brief Contains the Server class definition.

namespace NetSim {

//! \defgroup NetSimServer Server
//! \brief Defines the Server entity in the network simulation environment.

/**
 * @class Server
 * @ingroup NetSimServer
 * @brief Represents a Server entity in the simulation.
 *
 * The Server class extends the Host class, introducing the capability to serve
 * HTML content, handle DNS requests, and participate in HTTP and TCP
 * interactions.
 */
class Server : public Host {
public:
  /**
   * @brief Default constructor.
   *
   * Creates a default instance of the Server.
   */
  Server() = default;

  /**
   * @brief Parameterized constructor to initialize server attributes.
   *
   * @param networkCard The network card configuration for the server.
   * @param domain The domain associated with the server.
   * @param html The HTML content that this server can serve.
   */
  Server(const NetworkCard &networkCard, const QString &domain,
         const QString &html);

  /**
   * @brief Retrieves the domain associated with the server.
   *
   * @retval QString The domain of the server.
   */
  QString domain() const;

  /**
   * @brief Processes an incoming data package.
   *
   * @param data The package that the server has received.
   *
   * This function checks the type of the incoming package, determines the
   * appropriate strategy to process it, and delegates the processing to that
   * strategy. Strategies can include DNS response, HTTP response, etc.
   */
  void receivePackage(Package data) override;

  /**
   * @brief Retrieves the HTML content associated with the server.
   *
   * @retval QString The HTML content that this server can serve.
   */
  QString htmlFile() const;

private:
  //! @brief The domain associated with the server.
  QString m_domain{};

  //! @brief The HTML content that this server can serve.
  QString m_htmlFile{};
};

} // namespace NetSim

#endif // SERVER_H
