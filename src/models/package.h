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
    Package(const QString& content);

    const char* getData()const{
        return content;
    }

    void addHeader(const Header& header){
        headers.append(header);
    }
    
};

#endif // PACKAGE_H
