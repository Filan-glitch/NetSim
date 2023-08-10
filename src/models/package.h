#ifndef PACKAGE_H
#define PACKAGE_H

#include <QList>
#include "src/protocols/header.h"
#include "ipaddress.h"
#include "macaddress.h"
#include "port.h"

class Package
{
private:
    Header& getHeaderByType(const HeaderType &type);

    void deleteHeaderByType(const HeaderType &type);

    HeaderAttribute getHeaderAttributeByName(const Header &header, const QString &name) const;

    QList<Header> headers;

    QString info;

    QString content;

public:
    Package();

    Package(const QString& info);

    Package(const QString& info, const QString& content);

    QString getContent() const;

    QList<Header> getHeaders() const;

    void addHeader(const Header &header);

    void setContent(const QString &content);

    QString getInfo() const;

    quint16 getLength() const;

    void changePortAndIP(const Port &number, const IPAddress &address, bool src);

    void changeEthernetHeader(const MACAddress &srcAddress, const MACAddress &destAddress);

    Header &operator[](const HeaderType &type);
};

#endif // PACKAGE_H
