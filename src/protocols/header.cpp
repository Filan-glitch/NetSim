#include "header.h"



Header::Header() {}

Header::Header(HeaderType headerType, const QList<HeaderAttribute *> &headerList) : headerType(headerType), headerList(headerList) {}

Header::~Header() {
    for(int i = 0; i < headerList.size(); i++)
        delete headerList[i];
}

void Header::addHeaderAttribute(HeaderAttribute *headerAttribute){
    headerList.append(headerAttribute);
}

void Header::setHeaderType(const HeaderType &headerType){
    this->headerType = headerType;
}

QList<HeaderAttribute *> Header::getHeaderList() const {
    return headerList;
}

HeaderType &Header::getType() {
    return headerType;
}
