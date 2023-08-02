#ifndef HEADER_H
#define HEADER_H

#include <QList>
#include "headerAttribute.h"

/**
 * @brief The HeaderType enum
 * @par Represents the type of a header
 */
enum HeaderType {HTTP, TCP, UDP, IP, MAC};

/**
 * @brief The Header class
 * @par Represents the Header of a Protocol like UDP, TCP etc.
 */
class Header
{
private:
    HeaderType headerType;
protected:
    QList<HeaderAttribute*> headerList;
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
    Header(HeaderType headerType, const QList<HeaderAttribute*> &headerList);

    virtual ~Header();

    virtual void addHeaderAttribute(HeaderAttribute* headerAttribute);

    virtual void setHeaderType(const HeaderType& headerType);

    virtual QList<HeaderAttribute*> getHeaderList() const;

    virtual HeaderType& getType();
};

#endif // HEADER_H
