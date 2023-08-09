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
    Header& getHeaderByType(HeaderType type);
    void deleteHeaderByType(HeaderType type);
    HeaderAttribute getHeaderAttributeByName(Header header, QString name);

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
    void setContent(QString content);

    QString getInfo() const;

    quint16 getLength() const;

    void changePortAndIP(Port number, IPAddress address, bool src);

    void changeEthernetHeader(MACAddress srcAddress, MACAddress destAddress);
    
};

#endif // PACKAGE_H
