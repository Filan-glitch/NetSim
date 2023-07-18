#ifndef HEADER_H
#define HEADER_H

#include <QList>
#include "headerAttribute.h"
/**
 * @brief The Header class
 * @par Represents the Header of a Protocol like UDP, TCP etc.
 */
class Header
{
private:
    QList<HeaderAttribute> headerList;
public:
    /**
     * @brief Header
     * @param headerList
     * @par Constructor of a Header, needs a QList with all HeaderAttributes
     */
    Header(const QList<HeaderAttribute> &headerList);
};

#endif // HEADER_H
