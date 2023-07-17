#ifndef HEADER_H
#define HEADER_H

#include <QList>
#include "headerAttribute.h"

class Header
{
private:
    QList<HeaderAttribute> headerList;
public:
    Header(const QList<HeaderAttribute> &headerList);
};

#endif // HEADER_H
