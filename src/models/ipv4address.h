#ifndef IPV4ADDRESS_H
#define IPV4ADDRESS_H

#include "src/models/rawdata.h"
#include <QRandomGenerator>
#include <QString>
#include <QTextStream>
#include <QVector>

//! \file ipv4address.h
//! \ingroup NetSimIPv4Address
//! \brief Contains the IPv4Address class definition.

namespace NetSim {

//! \defgroup NetSimIPv4Address IPv4 Address
//! \brief Represents an IPv4 address.

/**
 * @class IPv4Address
 * @ingroup NetSimIPv4Address
 * @brief Represents an IPv4 address.
 *
 * This class provides functionalities to represent an IPv4 address,
 * and offers various conversion utilities like converting to string,
 * array or an integer format.
 */
class IPv4Address {
public:
  //! @brief Default constructor.
  IPv4Address() = default;

  /**
   * @brief Constructs an IPv4Address from a given byte array.
   *
   * @param address A byte array representing the IPv4 address.
   */
  IPv4Address(const RawData &address);

  //! @brief Converts the IPv4 address to a string format.
  QString toString() const;

  //! @brief Converts the IPv4 address to a byte array.
  RawData toArray() const;

  /**
   * @brief Generates a random IPv4 address.
   *
   * If the isLocal parameter is true, the last byte of the IPv4 address is set
   * to 1.
   *
   * @param isLocal Whether the IPv4 address should be local or not.
   * @return A random IPv4 address.
   */
  static IPv4Address getRandomAddress(bool isLocal = false);

private:
  //! @brief A byte array representing the IPv4 address.
  RawData m_address{32};
};
} // namespace NetSim

#endif // IPV4ADDRESS_H
