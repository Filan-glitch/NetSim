#ifndef PACKAGEDATABASE_H
#define PACKAGEDATABASE_H

#include "src/models/package.h"
#include <QList>

namespace NetSim {
class PackageDatabase;
}

class PackageDatabase {
public:
  QList<Package> *packageList();

  static PackageDatabase *instance();

private:
  PackageDatabase();

  QList<Package> m_packageList;
};

#endif // PACKAGEDATABASE_H
