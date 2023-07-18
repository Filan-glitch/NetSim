#ifndef PACKAGE_H
#define PACKAGE_H

#include <QList>
#include "../protocols/header.h"

class Package
{
private:
    QList<Header> headers;
    char content[1500];
public:
    Package();

    const char* getData()const{
        return content;
    }
};

#endif // PACKAGE_H
