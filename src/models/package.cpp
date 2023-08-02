#include "package.h"
#include "src/protocols/Headernotfoundexception.h"

Package::Package() {}

Package::Package(const QString &info, const QString &content) : headers(QList<Header>()), info(info), content(content)
{}

QString Package::getData() const {
    return content;
}

QList<Header> Package::getHeaders() const {
    return headers;
}

Header Package::getHeaderByType(const HeaderType &type) const {
    for (int i = 0; i < this->headers.size(); i++) {
        if (this->headers.at(i).getType() == type) {
            return this->headers[i];
        }
    }
    throw HeaderNotFoundException("Header of type " + QString::number(type) + " not found");
}

void Package::addHeader(const Header &header){
    headers.append(header);
}

QString Package::getInfo() const {
    return info;
}
