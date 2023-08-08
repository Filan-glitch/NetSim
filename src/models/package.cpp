#include "package.h"
#include "src/protocols/Headernotfoundexception.h"
#include "src/management/logger.h"
#include "src/protocols/tcp.h"

#include <src/protocols/headerattributenotfoundexception.h>

Package::Package() {}

Package::Package(const QString &info) : headers(QList<Header>()), info(info), content(QString())
{}

Package::Package(const QString &info, const QString& content) : headers(QList<Header>()), info(info), content(content)
{}

QString Package::getContent() const {
    return content;
}

QList<Header> Package::getHeaders() const {
    return headers;
}

void Package::addHeader(const Header &header){
    headers.append(header);
}

QString Package::getInfo() const {
    return info;
}

void Package::setContent(QString content){
    this->content = content;
}

quint16 Package::getLength() const {
    quint16 length = getContent().length();
    for(const Header& header : headers){
        length += header.getHeaderLength();
    }
    return length;
}

void Package::changePortAndIP(Port number, IPAddress address, bool src){
    Header copyHeader;
    bool udp = false;

    try{
        copyHeader = this->getHeaderByType(HeaderType::TCP);
    }
    catch(HeaderNotFoundException hnfe){
        try{
            copyHeader = getHeaderByType(HeaderType::UDP);
            udp = true;
        }
        catch(HeaderNotFoundException hnfe2){
            qDebug() << hnfe2.getErrorMessage() << " in Package::changePort";
        }
    }

    udp ? deleteHeaderByType(HeaderType::UDP) : deleteHeaderByType(HeaderType::TCP);

    //TODO CONTINUE
}

void Package::changeEthernetHeader(MACAddress srcAddress, MACAddress destAddress){

}

Header Package::getHeaderByType(HeaderType type){
    for(Header header : this->headers){
        if(header.getType() == type){
            return header;
        }
    }
    throw HeaderNotFoundException("Could not find Header in Package::getHeaderByType");
}

void Package::deleteHeaderByType(HeaderType type){
    for(int i = 0; i < this->headers.size(); i++){
        if(headers.at(i).getType() == type){
            headers.removeAt(i);
        }
    }
    throw HeaderNotFoundException("Could not find Header");
}

HeaderAttribute Package::getHeaderAttributeByName(Header header, QString name){
    for(HeaderAttribute attribute : header.getHeaderList()){
        if(attribute.getName() == name){
            return attribute;
        }
    }
    throw HeaderAttributeNotFoundException("Could not find HeaderAttribute");
}
