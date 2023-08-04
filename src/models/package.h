#ifndef PACKAGE_H
#define PACKAGE_H

#include <QList>
#include "src/protocols/header.h"

class Package
{
private:
    QList<Header> headers;
    QString info;
    QString content;
public:
    Package();
    Package(const QString& info, const QString &content);

    QString getContent() const;

    QList<Header> getHeaders() const;

    Header getHeaderByType(const HeaderType& type) const;

    void addHeader(const Header &header);
    void setContent(QString content);

    QString getInfo() const;

    quint16 getLength() const;
    
};

#endif // PACKAGE_H
