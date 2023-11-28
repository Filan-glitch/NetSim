#ifndef PORT_H
#define PORT_H

#include "src/models/rawdata.h"

//! \file port.h
//! \ingroup NetSimPort
//! \brief Contains the Port class definition.

namespace NetSim {

//! \defgroup NetSimPort Port
//! \brief Represents a network port.

/**
 * @class Port
 * @ingroup NetSimPort
 * @brief Represents a network port.
 *
 * This class provides functionalities to represent a network port,
 * which is a 16-bit number commonly used in networking to specify
 * the endpoint in a network address.
 */
class Port {
public:
  //! @brief Default constructor.
  Port() = default;

  //! @brief Constructs a port with a specified port number.
  explicit Port(RawData portNumber);

  //! @brief Returns the port number.
  RawData portNumber() const;

  //! @brief Converts the port number to an array of bytes.
  RawData data() const;

  //! @brief Returns a random port.
  static Port getRandomPort();

private:
  //! @brief The port number.
  RawData m_portNumber{16};
};
} // namespace NetSim

#endif // PORT_H
