#ifndef HEADER_H
#define HEADER_H

#include <QList>
#include "headerAttribute.h"

/**
 * @brief The HeaderType enum
 * @par Represents the type of a header
 */
enum HeaderType {HTTP, DNS, TCP, UDP, IP, MAC, UNKNOWN};

/**
 * @brief The Header class
 * @par Represents the Header of a Protocol like UDP, TCP etc.
 */
class Header
{
private:
    HeaderType headerType;
protected:
    QList<HeaderAttribute> headerList;
public:
    /**
     * @brief Header
     * @par Constructor of a Header
     */
    Header();

    /**
     * @brief Header
     * @par Constructor of a Header
     * @param headerType
     * @param headerList
     */
    Header(const HeaderType &headerType, const QList<HeaderAttribute> &headerList);

    void addHeaderAttribute(const HeaderAttribute &headerAttribute);

    void setHeaderType(const HeaderType& headerType);

    QList<HeaderAttribute> getHeaderList() const;

    HeaderType getType() const;

    quint16 getHeaderLength() const;
};

#endif // HEADER_H
