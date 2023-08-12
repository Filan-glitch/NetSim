#ifndef PORT_H
#define PORT_H

#include <QString>

//! \file port.h
//! \ingroup NetSimPort
//! \brief Contains the Port class definition.

namespace NetSim {

//! \defgroup NetSimPort NetSim Port
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
  Port();

  //! @brief Constructs a port with a specified port number.
  explicit Port(quint16 portNumber);

  //! @brief Returns the port number.
  quint16 portNumber() const;

  //! @brief Converts the port number to an array of bytes.
  QVector<quint8> toArray() const;

  //! @brief Returns a random port.
  static Port getRandomPort();

  //! @brief Compares the port number with another port.
  bool operator<(const Port &other) const;

private:
  //! @brief The port number.
  quint16 m_portNumber;
};
} // namespace NetSim

#endif // PORT_H
