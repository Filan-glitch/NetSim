#include "package.h"
#include "src/protocols/Headernotfoundexception.h"

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

void Package::setContent(const QString &content){
    this->content = content;
}

quint16 Package::getLength() const {
    quint16 length = getContent().length();
    for(const Header& header : headers){
        length += header.getHeaderLength();
    }
    return length;
}

void Package::changePortAndIP(const Port &number, const IPAddress &address, bool src){
    //Getting the right Header

    //Changing the Ports
    if(src){
        HeaderAttribute srcPort("Source Port", 16, number.getPortNumber());
        try {
            (*this)[HeaderType::TCP]["Source Port"].setContent(srcPort.getContentAsArray());
        } catch (HeaderNotFoundException e) {
            qDebug() << e.getErrorMessage() << " Package is not a TCP Package. Could not change the Source Port.";
        }
        try {
            (*this)[HeaderType::UDP]["Source Port"].setContent(srcPort.getContentAsArray());
        } catch (HeaderNotFoundException e) {
            qDebug()<< e.getErrorMessage() << " Package is not a UDP Package. Could not change the Source Port.";
        }
    }
    else{
        HeaderAttribute destPort("Destination Port", 16, number.getPortNumber());
        try {
            (*this)[HeaderType::TCP]["Destination Port"].setContent(destPort.getContentAsArray());
        } catch (HeaderNotFoundException e) {
            qDebug()<< e.getErrorMessage() << " Package is not a TCP Package. Could not change the Destination Port.";
        }
        try {
            (*this)[HeaderType::UDP]["Destination Port"].setContent(destPort.getContentAsArray());
        } catch (HeaderNotFoundException e) {
            qDebug()<< e.getErrorMessage() << " Package is not a UDP Package. Could not change the Destination Port.";
        }
    }

    if(src){
        try{
            (*this)[HeaderType::IP]["Source Address"].setContent(address.getAddressAsArray());
        } catch(HeaderNotFoundException e){
            qDebug()<< e.getErrorMessage() << " Package is not an IP Package. Could not change the Source Address.";
        }

    }
    else{
        try{
            (*this)[HeaderType::IP]["Destination Address"].setContent(address.getAddressAsArray());
        } catch(HeaderNotFoundException e){
            qDebug() << e.getErrorMessage() << " Package is not an IP Package. Could not change the Destination Address.";
        }
    }
}

void Package::changeEthernetHeader(const MACAddress &srcAddress, const MACAddress &destAddress){

    //Changing MAC Addresses
    try{
        (*this)[HeaderType::MAC]["Destination MAC Address"].setContent(destAddress.getAddressAsArray());
    }catch(HeaderNotFoundException e){
        qDebug() << e.getErrorMessage() << " Package is not a MAC Package. Could not change the Destination MAC Address.";
    }

    try{
     (*this)[HeaderType::MAC]["Source MAC Address"].setContent(srcAddress.getAddressAsArray());
    }catch(HeaderNotFoundException e){
        qDebug() << e.getErrorMessage() << " Package is not a MAC Package. Could not change the Source MAC Address.";
    }
}

Header &Package::operator[](const HeaderType &type)
{
    for(int i = 0; i < headers.size();i++){
        if(type == headers[i].getType()){
            return headers[i];
        }
    }
    throw HeaderNotFoundException("Could not find Header with type " + QString::number(type));
}

Header& Package::getHeaderByType(const HeaderType &type){
    for(int i = 0; i < headers.size();i++){
        if(type == headers[i].getType()){
            return headers[i];
        }
    }
    throw HeaderNotFoundException("Could not find Header in Package::getHeaderByType");
}

void Package::deleteHeaderByType(const HeaderType &type){
    for(int i = 0; i < this->headers.size(); i++){
        if(headers.at(i).getType() == type){
            headers.removeAt(i);
        }
    }
    throw HeaderNotFoundException("Could not find Header");
}

HeaderAttribute Package::getHeaderAttributeByName(const Header &header, const QString &name) const {
    for(HeaderAttribute attribute : header.getHeaderList()){
        if(attribute.getName() == name){
            return attribute;
        }
    }
    throw HeaderAttributeNotFoundException("Could not find HeaderAttribute");
}
