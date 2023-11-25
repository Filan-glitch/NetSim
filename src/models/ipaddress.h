#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QRandomGenerator>
#include <QString>
#include <QTextStream>
#include <QVector>
#include <QBitArray>

//! \file ipaddress.h
//! \ingroup NetSimIPAddress
//! \brief Contains the IPAddress class definition.

namespace NetSim {

//! \defgroup NetSimIPAddress IP Address
//! \brief Represents an IP address.

/**
 * @class IPAddress
 * @ingroup NetSimIPAddress
 * @brief Represents an IPv4 address.
 *
 * This class provides functionalities to represent an IPv4 address,
 * and offers various conversion utilities like converting to string,
 * array or an integer format.
 */
class IPAddress {
public:
  //! @brief Default constructor.
  IPAddress() = default;

  /**
   * @brief Constructs an IPAddress from a given byte array.
   *
   * @param address A byte array representing the IP address.
   */
  IPAddress(const QBitArray &address);

  //! @brief Converts the IP address to a string format.
  QString toString() const;

  //! @brief Converts the IP address to a byte array.
  QBitArray toArray() const;

  /**
   * @brief Generates a random IP address.
   *
   * If the isLocal parameter is true, the last byte of the IP address is set
   * to 1.
   *
   * @param isLocal Whether the IP address should be local or not.
   * @return A random IP address.
   */
  static IPAddress getRandomAddress(bool isLocal = false);

  /**
   * @brief Overload of the equality operator.
   *
   * Checks if this IP address is equal to another based on their integer
   * format.
   *
   * @param other The other IP address to compare against.
   * @return true if the IP addresses are equal, false otherwise.
   */
  bool operator==(const IPAddress &other) const;

private:
  //! @brief A byte array representing the IP address.
  QBitArray m_address{32, false};
};
} // namespace NetSim

#endif // IPADDRESS_H
