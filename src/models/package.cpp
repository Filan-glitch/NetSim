#include "package.h"
#include "src/protocols/Headernotfoundexception.h"
#include "src/management/logger.h"
#include "src/protocols/tcp.h"
#include "src/protocols/ipv4.h"

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
    //Getting the right Header
    Header header;
    try{
        header = this->getHeaderByType(HeaderType::TCP);
    }
    catch(HeaderNotFoundException hnfe){
        try{
            header = this->getHeaderByType(HeaderType::UDP);
        }
        catch(HeaderNotFoundException hnfe){
            qDebug() << hnfe.getErrorMessage() << " in Package::changePortAndIP";
        }
    }

    //Changing the Ports
    if(src && (header["Source Port"] != nullptr)){
        HeaderAttribute srcPort("Source Port", 16, number.getPortNumber());
        header["Source Port"]->setContent(srcPort.getContentAsArray());
    }
    else if(!src && (header["Destination Port"] != nullptr)){
        HeaderAttribute destPort("Destination Port", 16, number.getPortNumber());
        header["Destination Port"]->setContent(destPort.getContentAsArray());
    }
    else{
        qDebug() << "Source or Destinationport is nullptr in Package::changePortAndIP";
    }

    //TODO recalc Checksum

    Header ipHeader;
    try{
        header = this->getHeaderByType(HeaderType::IP);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in Package::changePortAndIP";
    }

    if(src && (ipHeader["Source Address"] != nullptr)){
        ipHeader["Source Address"]->setContent(address.getAddressAsArray());
    }
    else if(!src && (ipHeader["Destination Address"] != nullptr)){
        ipHeader["Destination Address"]->setContent(address.getAddressAsArray());
    }

    //TODO Recalc Checksum
}

void Package::changeEthernetHeader(MACAddress srcAddress, MACAddress destAddress){
    //Getting the Ethernet II Header
    Header ethernetHeader;
    try{
        ethernetHeader = this->getHeaderByType(HeaderType::MAC);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in Package::changeEthernetHeader";
    }

    //Changing MAC Addresses
    if(ethernetHeader["Destination MAC Address"] != nullptr){
       ethernetHeader["Destination MAC Address"]->setContent(destAddress.getAddressAsArray());
    }
    else{
       qDebug() << "Destination MAC Address is nullptr in Package::changeEthernetHeader";
    }

    if(ethernetHeader["Source MAC Address"] != nullptr){
    ethernetHeader["Source MAC Address"]->setContent(srcAddress.getAddressAsArray());
    }
    else{
    qDebug() << "Source MAC Address is nullptr in Package::changeEthernetHeader";
    }
}

Header& Package::getHeaderByType(HeaderType type){
    for(int i = 0; i < headers.size();i++){
        if(type == headers[i].getType()){
            return headers[i];
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
