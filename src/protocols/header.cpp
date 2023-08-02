#include "header.h"



Header::Header() {}

Header::Header(const HeaderType &headerType, const QList<HeaderAttribute> &headerList) : headerType(headerType), headerList(headerList) {}


void Header::addHeaderAttribute(const HeaderAttribute &headerAttribute){
    headerList.append(headerAttribute);
}

void Header::setHeaderType(const HeaderType &headerType){
    this->headerType = headerType;
}

QList<HeaderAttribute> Header::getHeaderList() const {
    return headerList;
}

HeaderType Header::getType() const {
    return headerType;
}
