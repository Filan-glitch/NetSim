#ifndef PACKAGE_H
#define PACKAGE_H

#include <QList>
#include "src/protocols/header.h"

class Package
{
private:
    QList<Header*> headers;
    QString info;
    QString content;
public:
    Package(const QString& info, const QString &content);

    ~Package();

    QString getData() const;

    QList<Header*> getHeaders() const;

    Header* getHeaderByType(const HeaderType& type) const;

    void setContent(QString content);

    void addHeader(Header* header);

    QString getInfo() const;
    
};

#endif // PACKAGE_H
