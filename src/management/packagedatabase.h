#ifndef PACKAGEDATABASE_H
#define PACKAGEDATABASE_H

#include "src/models/package.h"
#include <QList>

class PackageDatabase
{
private:
    PackageDatabase();

    QList<Package> m_packageList;

public:
    QList<Package>* packageList();

    static PackageDatabase* instance();
};

#endif // PACKAGEDATABASE_H
