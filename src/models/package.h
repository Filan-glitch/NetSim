#ifndef PACKAGE_H
#define PACKAGE_H

#include <QList>
#include "../protocols/header.h"

class Package
{
private:
    QList<Header> headers;
    QString content;
public:
    Package(const QString& content);
    void addHeader(const Header& header);
};

#endif // PACKAGE_H
