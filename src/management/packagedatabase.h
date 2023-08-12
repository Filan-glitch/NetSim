#ifndef PACKAGEDATABASE_H
#define PACKAGEDATABASE_H

#include "src/models/package.h"
#include <QList>

//! \file packagedatabase.h
//! \ingroup NetSimPackageDatabase
//! \brief Contains the PackageDatabase class definition.

namespace NetSim {
class PackageDatabase;
}

//! \defgroup NetSimPackageDatabase NetSim Package Database
//! \brief Provides utilities for managing a list of `Package` objects.

/**
 * @class PackageDatabase
 * @ingroup NetSimPackageDatabase
 * @brief A singleton class to manage and provide access to a list of `Package`
 * objects.
 *
 * The PackageDatabase class centralizes the management and storage of packages.
 * Being a singleton, it ensures that there's a single instance of the package
 * list throughout the application, ensuring consistent and coordinated access.
 */
class PackageDatabase {
public:
  /**
   * @brief Retrieves the list of packages.
   *
   * @retval QList<Package>* A pointer to the list of packages.
   */
  QList<Package> *packageList();

  /**
   * @brief Provides access to the singleton instance of the PackageDatabase.
   *
   * @retval PackageDatabase* The singleton instance of the PackageDatabase.
   * @see instance
   */
  static PackageDatabase *instance();

private:
  //! @brief Private constructor to ensure single instance creation.
  PackageDatabase();

  //! @brief A list storing all the `Package` objects.
  QList<Package> m_packageList;
};

#endif // PACKAGEDATABASE_H
