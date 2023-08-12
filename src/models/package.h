#ifndef PACKAGE_H
#define PACKAGE_H

#include "ipaddress.h"
#include "macaddress.h"
#include "port.h"
#include "src/protocols/header.h"
#include <QList>

//! \file package.h
//! \ingroup NetSimPackage
//! \brief Contains the Package class definition.

namespace NetSim {

class Package;
} // namespace NetSim

//! \defgroup NetSimPackage NetSim Package
//! \brief Represents a network package with multiple headers.

/**
 * @class Package
 * @ingroup NetSimPackage
 * @brief Represents a network package.
 *
 * This class provides functionalities to represent a network package,
 * which can contain multiple headers and a payload. The package can
 * be modified by adding/removing headers or changing its content.
 */
class Package {
public:
  //! @brief Default constructor.
  Package();

  //! @brief Constructs a package with information.
  explicit Package(const QString &info);

  //! @brief Constructs a package with information and content.
  Package(const QString &info, const QString &content);

  //! @brief Returns the package's content.
  QString content() const;

  //! @brief Returns the list of headers.
  QList<Header> headers() const;

  //! @brief Returns the package's information.
  QString info() const;

  //! @brief Returns the total size of the package.
  quint16 size() const;

  //! @brief Adds a new header to the package.
  void addHeader(const Header &header);

  //! @brief Sets the package's content.
  void setContent(const QString &content);

  //! @brief Modifies the IP and port headers.
  void changePortAndIP(const Port &number, const IPAddress &address, bool src);

  //! @brief Modifies the Ethernet header.
  void changeEthernetHeader(const MACAddress &srcAddress,
                            const MACAddress &destAddress);

  //! @brief Returns a reference to a specific header.
  Header &operator[](const NetSim::HeaderType &type);

  //! @brief Returns a specific header.
  Header operator[](const NetSim::HeaderType &type) const;

private:
  //! @brief List of headers.
  QList<Header> m_headers;

  //! @brief Package's information.
  QString m_info;

  //! @brief Package's content.
  QString m_content;

  //! @brief Deletes a header of a specific type.
  void deleteHeaderByType(const NetSim::HeaderType &type);

  //! @brief Returns a header attribute by its name.
  HeaderAttribute getHeaderAttributeByName(const Header &header,
                                           const QString &name) const;
};

#endif // PACKAGE_H
