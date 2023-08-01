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
    Header() {}

    /**
     * @brief Header
     * @par Constructor of a Header
     * @param headerType
     * @param headerList
     */
    Header(HeaderType headerType, const QList<HeaderAttribute*> &headerList) : headerType(headerType), headerList(headerList) {}

    virtual ~Header() {
        for(int i = 0; i < headerList.size(); i++)
            delete headerList[i];
    }

    virtual void addHeaderAttribute(HeaderAttribute* headerAttribute){
        headerList.append(headerAttribute);
    }

    virtual void setHeaderType(const HeaderType& headerType){
        this->headerType = headerType;
    }

    virtual QList<HeaderAttribute*> getHeaderList() const {
        return headerList;
    }

    virtual HeaderType& getType() {
        return headerType;
    }
};

#endif // HEADER_H
