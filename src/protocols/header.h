#ifndef HEADER_H
#define HEADER_H

//! \file header.h
//! \ingroup NetSimHeader
//! \brief Contains the Header class definition and related enumerations.

#include "headerAttribute.h"
#include <QDebug>
#include <QList>

namespace NetSim {

//! \defgroup NetSimHeader Header
//! \brief Provides functionalities related to the headers of different
//! protocols.

/**
 * @enum HeaderType
 * @ingroup NetSimHeader
 * @brief Enumeration for the type of headers available.
 */
enum HeaderType { HTTP, DNS, TCP, UDP, IP, MAC, UNKNOWN };

/**
 * @class Header
 * @ingroup NetSimHeader
 * @brief Class representing headers for different protocols.
 */
class Header {
public:
  /**
   * @brief Default constructor.
   */
  Header() = default;

  /**
   * @brief Parameterized constructor.
   *
   * @param headerType Type of header.
   * @param headerList List of header attributes.
   */
  Header(const HeaderType &headerType,
         const QList<HeaderAttribute> &headerList);

  /**
   * @brief Adds a header attribute to the header.
   *
   * @param headerAttribute The header attribute to be added.
   */
  void addHeaderAttribute(const HeaderAttribute &headerAttribute);

  /**
   * @brief Sets the header type.
   *
   * @param headerType Type of the header.
   */
  void setHeaderType(const HeaderType &headerType);

  /**
   * @brief Retrieves the list of header attributes.
   *
   * @retval QList<HeaderAttribute> List of header attributes.
   */
  QList<HeaderAttribute> headerList() const;

  /**
   * @brief Retrieves the header type.
   *
   * @retval HeaderType Type of the header.
   */
  HeaderType type() const;

  /**
   * @brief Calculates the size of the header.
   *
   * @retval quint16 Size of the header in bytes.
   */
  quint16 size() const;

  /**
   * @brief Overloaded subscript operator to get a header attribute by its name.
   *
   * @param name Name of the header attribute.
   * @retval HeaderAttribute& Reference to the header attribute.
   * @throws HeaderAttributeNotFoundException If the named attribute is not
   * found.
   */
  HeaderAttribute &operator[](const QString &name);

private:
  HeaderType m_headerType{HeaderType::UNKNOWN}; //!< Header type.
  QList<HeaderAttribute> m_headerList{};        //!< List of header attributes.
};

} // namespace NetSim

#endif // HEADER_H
