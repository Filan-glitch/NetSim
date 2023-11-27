#ifndef PACKAGE_H
#define PACKAGE_H

#include "src/models/rawdata.h"
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
  Package(const QString &info, const RawData &content);

  //! @brief Returns the package's content.
  RawData content() const;

  //! @brief Returns the package's information.
  QString info() const;

  //! @brief Returns the total size of the package.
  qsizetype size() const;

  //! @brief Sets the package's content.
  void setContent(const RawData &content);


private:
    //! @brief Package's content.
    RawData m_content{};

    //! @brief Package's information.
    QString m_info{"Basic Description"};
};
} // namespace NetSim

#endif // PACKAGE_H
