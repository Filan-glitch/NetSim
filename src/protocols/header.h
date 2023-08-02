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
    QList<HeaderAttribute> headerList;
public:
    /**
     * @brief Header
     * @param headerList
     * @param headerType
     * @par Constructor of a Header, needs a QList with all HeaderAttributes
     */
    Header(const HeaderType& headerType, const QList<HeaderAttribute> &headerList);

    Header();

    virtual ~Header(){

    }

    virtual void addHeaderAttribute(const HeaderAttribute& headerAttribute){
        headerList.append(headerAttribute);
    }

    virtual void setHeaderType(const HeaderType& headerType){
        this->headerType = headerType;
    }

    virtual QList<HeaderAttribute> getHeaderList() const {
        return headerList;
    }

    virtual HeaderType& getType() {
        return headerType;
    }
};

#endif // HEADER_H
