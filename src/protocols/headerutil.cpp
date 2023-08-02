#include "Headernotfoundexception.h"
#include "headerattributenotfoundexception.h"
#include "headerutil.h"
#include "src/management/logger.h"
#include <src/models/ipaddress.h>
#include <src/models/macaddress.cpp>

HeaderUtil::HeaderUtil()
{

}

Header* HeaderUtil::getHeaderByType(const HeaderType &type, const Package &data){
    QList<Header*> headerList = data.getHeaders();
    for(auto header : headerList){
        if(header->getType() == type){
            return header;
        }
    }
    throw HeaderNotFoundException("This Headertype does not exist: ");
}

HeaderAttribute HeaderUtil::getHeaderAttributeByName(const QString &name, const Header &header){
    QList<HeaderAttribute> attributeList = header.getHeaderList();
    for(auto& attribute : attributeList){
        if(attribute.getName() == name){
            return attribute;
        }
    }
    QString errorMessage = "This HeaderAttribute does not exist in the given Header: ";
    errorMessage.append(name);
    throw HeaderAttributeNotFoundException(errorMessage);
}


QString HeaderUtil::getHTTPAttributeAsString(const Package &data, const QString attributeName){
    //Getting the Header
    Header* header;
    try{
        header = getHeaderByType(HeaderType::HTTP, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::ggetAttributeAsString";
    }

    //Getting the attribute
    quint8* attribute;
    quint32 attributeSize;
    try{
        attribute = getHeaderAttributeByName(attributeName, *header).getContentAsArray();
        attributeSize = getHeaderAttributeByName(attributeName, *header).getSizeInBit();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getAttributeAsString";
    }

    //Converting to String
    QString returnString;
    for(quint32 i = 0; i < attributeSize/8;i++){
        returnString.append(static_cast<char>(attribute[i]));
    }
    delete header;
    delete attribute;
    return returnString;
}

QString HeaderUtil::getPort(const Package& data, bool src){
    //Getting the right header
    Header* header;
    try{
        header = getHeaderByType(HeaderType::TCP, data);
    }
    catch(HeaderNotFoundException hnfe){
        try{
            header = getHeaderByType(HeaderType::UDP,data);
        }
        catch(HeaderNotFoundException hnfe){
            qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getPort";
        }
    }

    //Getting the source or destination port
    quint8* attribute;
    if(src){
        try{
            attribute = getHeaderAttributeByName("Source Port", *header).getContentAsArray();
        }
        catch(HeaderAttributeNotFoundException hanfe){
            qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getPort";
        }
    }
    else{
        try{
            attribute = getHeaderAttributeByName("Destination Port", *header).getContentAsArray();
        }
        catch(HeaderAttributeNotFoundException hanfe){
            qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getPort";
        }
    }

    quint16 port = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];

    delete header;
    delete attribute;
    return QString::number(port);
}

QString HeaderUtil::getTCPFlag(const Package &data, QString flagName){
    //Get header
    Header* header;
    try{
        header = getHeaderByType(HeaderType::TCP, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
    }

    //Get flags
    quint8* attribute;
       try{
           attribute = getHeaderAttributeByName("Flags", *header).getContentAsArray();
       }
       catch(HeaderAttributeNotFoundException hanfe){
           qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
       }

    //putting the flags from quint8* together to quint16
    quint16 flag = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];
    QString returnString;

    //checking ack flag
    if(flagName == "ACK"){
           ((flag >> 10) & 1) != 0 ? returnString = "true" : returnString = "false";
    }
    //checking rst flag
    if(flagName == "RST"){
           ((flag >> 12) & 1) != 0 ? returnString = "true" : returnString = "false";
    }
    //checking syn flag
    if(flagName == "SYN"){
           ((flag >> 13) & 1) != 0 ? returnString = "true" : returnString = "false";
    }
    //checking fin flag
    if(flagName == "FIN"){
           ((flag >> 14) & 1) != 0 ? returnString = "true" : returnString = "false";
    }
    if(flagName != "ACK" && flagName !="RST" && flagName !="SYN" && flagName != "FIN"){
           qDebug() << "This flag does not exist: " << flagName << " in HeaderUtil::getTCPFlag";
    }

    delete header;
    delete attribute;
    return returnString;
}

QString HeaderUtil::getIPAddress(const Package &data, bool src){
    //Getting the IP Header
    Header* header;
    try{
           header = getHeaderByType(HeaderType::IP, data);
    }
    catch(HeaderNotFoundException hnfe){
           qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getIPAddress";
    }

    quint8* attribute;
    //Getting the source or destination address
    if(src){
           try{
            attribute = getHeaderAttributeByName("Source Address", *header).getContentAsArray();
           }
           catch(HeaderAttributeNotFoundException hanfe){
            qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
           }
    }
    else{
           try{
            attribute = getHeaderAttributeByName("Destination Address", *header).getContentAsArray();
           }
           catch(HeaderAttributeNotFoundException hanfe){
            qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
           }
    }
    //Creating the IP Address
    IPAddress address(attribute);

    delete header;
    delete attribute;
    return address.getAddressAsDecString();
}

QString HeaderUtil::getIPFlag(const Package &data,  QString flagName){
    //Getting the IP Header
    Header* header;
    try{
           header = getHeaderByType(HeaderType::IP, data);
    }
    catch(HeaderNotFoundException hnfe){
           qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getIPAddress";
    }
    quint8* attribute;
    //Getting the flags
    try{
           attribute = getHeaderAttributeByName("Flags",*header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
          qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getIPFlag";
    }

    quint8 flags = attribute[0];
    QString returnString;
    delete header;

    //Checking which flag
    if(flagName=="DF"){
        ((flags >> 1) & 1) != 0 ? returnString = "true" : returnString = "false";
          delete attribute;
        return returnString;
    }
    if(flagName=="MF"){
        ((flags >> 2) & 1) != 0 ? returnString = "true" : returnString = "false";
        delete attribute;
        return returnString;
    }
    qDebug() << "This flag does not exist: " << flagName << " in HeaderUtil::getIPFlag";
    delete attribute;
    return "";
}

QString HeaderUtil::getIPNextProtocol(const Package &data){
    //Getting the IP Header
    Header* header;
    try{
        header = getHeaderByType(HeaderType::IP, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getIPAddress";
    }
    quint8* attribute;
    //Getting the next Protocol
    try{
        attribute = getHeaderAttributeByName("Protocol",*header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getIPNextProtocol";
    }

    delete header;
    //Returning the right String
    if(attribute[0] == 17){
        delete attribute;
        return "UDP";
    }
    if(attribute[0] == 6){
        delete attribute;
        return "TCP";
    }
    if(attribute[0] == 0){
        delete attribute;
        return "";
    }
    qDebug() << "Cannot find a following Protocol in HeaderUtil::getIPNextProtocol";
    delete attribute;
    return "";
}

QString HeaderUtil::getMacAddress(const Package &data, bool src){
    //Getting the Ethernet II Header
    Header* header;
    try{
        header = getHeaderByType(HeaderType::MAC, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getMacAddress";
    }

    //Getting the MAC Address
    quint8* attribute;
    if(src){
        try{
            attribute = getHeaderAttributeByName("Source MAC Address",*header).getContentAsArray();
        }
        catch(HeaderAttributeNotFoundException hanfe){
            qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getMacAddress";
        }
    }
    else{
        try{
            attribute = getHeaderAttributeByName("Destination MAC Address",*header).getContentAsArray();
        }
        catch(HeaderAttributeNotFoundException hanfe){
            qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getMacAddress";
        }
    }

    MACAddress address(attribute);
    delete attribute;
    delete header;
    return address.getAddressAsString();
}

QString HeaderUtil::getEtherType(const Package &data){
    //Getting the Ethernet II Header
    Header* header;
    try{
        header = getHeaderByType(HeaderType::MAC, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getMacAddress";
    }

    quint8* attribute;
    try{
        attribute = getHeaderAttributeByName("EtherType",*header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getEtherType";
    }

    quint16 etherType = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];
    delete header;

    if(etherType == 2048){
        delete attribute;
        return "IPv4";
    }
    if(etherType == 0){
        delete attribute;
        return "";
    }
    qDebug() << "No corresponding EtherType found in HeaderUtil::getEtherType";
    delete attribute;
    return "";
}
