#ifndef PROCESS_H
#define PROCESS_H

#include "src/models/ipv4address.h"
#include "src/network/socket.h"
#include <QString>

//! \file process.h
//! \ingroup Management
//! \brief Contains the Process class definition.

namespace NetSim {

class Host;

//! \defgroup NetSimProcess Process
//! \brief Represents a network process.

/**
 * @class Process
 * @brief Represents a network process.
 *
 * This class provides functionalities related to different types of network
 * processes such as HTTP, DNS, and TCP. It allows generating network packages
 * for different protocols and interacting with the associated host's network
 * card.
 */
class Process {
public:
  //! Default constructor.
  Process() = default;

  //! Constructor initializing a process with a destination port and a name.
  Process(const Port &destinationPort, const QString &name);

  //! Retrieves an editable associated socket reference.
  Socket &socket();

  //! Retrieve the associated socket.
  Socket socket() const;

  //! Retrieves the process's name.
  QString name() const;

  //! Sets the associated host.
  void setHost(Host *host);

  //! Retrieves a string representation of the process.
  QString toString() const;

private:
  QString m_name{};      //!< The name of the process.
  Socket m_socket{};     //!< The associated socket.
  Host *m_host{nullptr}; //!< The host associated with this process.
};
} // namespace NetSim

#endif // PROCESS_H
