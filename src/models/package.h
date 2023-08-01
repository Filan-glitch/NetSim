#ifndef PACKAGE_H
#define PACKAGE_H

#include <QList>
#include "src/protocols/header.h"

class Package
{
private:
    QList<Header*> headers;
    QString info;
    QString content;
public:
    Package(const QString& info, const QString &content) : headers(QList<Header*>()), info(info), content(content)
    {}

    ~Package(){
        for (int i = 0; i < headers.size(); i++) {
            delete headers[i];
        }
    }

    QString getData() const {
        return content;
    }

    QList<Header*> getHeaders() const {
        return headers;
    }

    Header* getHeaderByType(const HeaderType& type) const {
        for (int i = 0; i < headers.size(); i++) {
            if (headers[i]->getType() == type) {
                return headers[i];
            }
        }
        return new Header();
    }

    void addHeader(Header* header){
        headers.append(header);
    }

    QString getInfo() const {
        return info;
    }
    
};

#endif // PACKAGE_H
