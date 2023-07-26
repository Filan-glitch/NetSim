#ifndef PACKAGE_H
#define PACKAGE_H

#include <QList>
#include "src/protocols/header.h"

class Package
{
private:
    QList<Header> headers;
    QString content;
public:
    Package(const QString& content);

    QString getData() const{
        return content;
    }

    void addHeader(const Header& header){
        headers.append(header);
    }
    
};

#endif // PACKAGE_H
