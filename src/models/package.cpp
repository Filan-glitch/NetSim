#include "package.h"

Package::Package(const QString &info, const QString &content) : headers(QList<Header*>()), info(info), content(content)
{}

Package::~Package(){
    for (int i = 0; i < headers.size(); i++) {
        delete headers[i];
    }
}

QString Package::getData() const {
    return content;
}

QList<Header *> Package::getHeaders() const {
    return headers;
}

Header *Package::getHeaderByType(const HeaderType &type) const {
    for (int i = 0; i < headers.size(); i++) {
        if (headers[i]->getType() == type) {
            return headers[i];
        }
    }
    return new Header();
}

void Package::addHeader(Header *header){
    headers.append(header);
}

QString Package::getInfo() const {
    return info;
}
