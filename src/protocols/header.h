#ifndef HEADER_H
#define HEADER_H

#include <QList>
#include "headerAttribute.h"
#include <QDebug>

enum HeaderType {HTTP, DNS, TCP, UDP, IP, MAC, UNKNOWN};

class Header
{
private:
    HeaderType headerType;

protected:
    QList<HeaderAttribute> headerList;

public:
    Header();

    Header(const HeaderType &headerType, const QList<HeaderAttribute> &headerList);

    void addHeaderAttribute(const HeaderAttribute &headerAttribute);

    void setHeaderType(const HeaderType& headerType);

    QList<HeaderAttribute> getHeaderList() const;

    HeaderType getType() const;

    quint16 getHeaderLength() const;

    HeaderAttribute &operator[](const QString &name);
};

#endif // HEADER_H
