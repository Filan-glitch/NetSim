#ifndef PACKAGE_H
#define PACKAGE_H

#include <QBitArray>
#include <QString>

//! \file package.h
//! \ingroup NetSimPackage
//! \brief Contains the Package class definition.

namespace NetSim {

//! \defgroup NetSimPackage Package
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
  Package() = default;

  //! @brief Constructs a package with information.
  explicit Package(const QString &info);

  //! @brief Constructs a package with information and content.
  Package(const QString &info, const QBitArray &content);

  //! @brief Returns the package's content.
  QBitArray content() const;

  //! @brief Returns the package's information.
  QString info() const;

  //! @brief Returns the total size of the package.
  qsizetype size() const;

  //! @brief Sets the package's content.
  void setContent(const QBitArray &content);

  //! @brief Adds data to the package's content
  void appendData(const QBitArray &data);

private:
   //! @brief Package's content.
   QBitArray m_content;

  //! @brief Package's information.
  QString m_info{"Basic Description"};
};
} // namespace NetSim

#endif // PACKAGE_H
