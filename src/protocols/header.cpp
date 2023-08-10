#include "header.h"
#include "src/protocols/headerattributenotfoundexception.h"

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

quint16 Header::getHeaderLength() const {
    quint16 length = 0;
    for(const HeaderAttribute &headerAttribute : headerList){
        length += headerAttribute.getSizeInBit();
    }
    return length / 8;
}

HeaderAttribute &Header::operator[](const QString &name){
    for(int i = 0; i < headerList.size(); i++){
        if(headerList.at(i).getName() == name){
            return headerList[i];
        }
    }
    qDebug() << "HeaderAttribute not found: " << name;
    throw HeaderAttributeNotFoundException(name);
}
