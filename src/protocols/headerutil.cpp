#include "Headernotfoundexception.h"
#include "headerattributenotfoundexception.h"
#include "headerutil.h"
#include "src/models/ipaddress.h"
#include "src/models/macaddress.cpp"
#include <QDebug>

HeaderUtil::HeaderUtil()
{

}

Header HeaderUtil::getHeaderByType(const HeaderType &type, const Package &data){
    QList<Header> headerList = data.getHeaders();
    for(auto header : headerList){
        if(header.getType() == type){
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


QString HeaderUtil::getHTTPAttributeAsString(const Package &data, const QString &attributeName){
    //Getting the Header
    Header header;
    try{
        header = getHeaderByType(HeaderType::HTTP, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::ggetAttributeAsString";
    }

    //Getting the attribute
    QVector<quint8> attribute;
    quint32 attributeSize;
    try{
        attribute = getHeaderAttributeByName(attributeName, header).getContentAsArray();
        attributeSize = getHeaderAttributeByName(attributeName, header).getSizeInBit();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getAttributeAsString";
    }

    //Converting to String
    QString returnString;
    for(quint32 i = 0; i < attributeSize/8;i++){
        returnString.append(static_cast<char>(attribute[i]));
    }
    return returnString;
}

QString HeaderUtil::getPort(const Package &data, bool src){
    //Getting the right header
    Header header;
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
    QVector<quint8> attribute;
    if(src){
        try{
            attribute = getHeaderAttributeByName("Source Port", header).getContentAsArray();
        }
        catch(HeaderAttributeNotFoundException hanfe){
            qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getPort";
        }
    }
    else{
        try{
            attribute = getHeaderAttributeByName("Destination Port", header).getContentAsArray();
        }
        catch(HeaderAttributeNotFoundException hanfe){
            qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getPort";
        }
    }

    quint16 port = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];

    return QString::number(port);
}

QString HeaderUtil::getTCPFlag(const Package &data, const QString &flagName){
    //Get header
    Header header;
    try{
        header = getHeaderByType(HeaderType::TCP, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
    }

    //Get flags
    QVector<quint8> attribute;
       try{
        attribute = getHeaderAttributeByName("Flags", header).getContentAsArray();
       }
       catch(HeaderAttributeNotFoundException hanfe){
           qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
       }

    //putting the flags from quint8* together to quint16
    quint16 flag = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];
    QString returnString;

    //checking URG flag
    if(flagName == "URG"){
           return "false";
    }
    //checking ack flag
    if(flagName == "ACK"){
           ((flag >> 10) & 1) != 0 ? returnString = "true" : returnString = "false";
    }
    //checking psh flag
    if(flagName == "PSH"){
           ((flag >> 11) & 1) != 0 ? returnString = "true" : returnString = "false";
    }
    //checking rst flag
    if(flagName == "RST"){
           return "false";
    }
    //checking syn flag
    if(flagName == "SYN"){
           ((flag >> 13) & 1) != 0 ? returnString = "true" : returnString = "false";
    }
    //checking fin flag
    if(flagName == "FIN"){
           ((flag >> 14) & 1) != 0 ? returnString = "true" : returnString = "false";
    }
    if(flagName != "URG" && flagName != "ACK" && flagName != "PSH" && flagName !="RST" && flagName !="SYN" && flagName != "FIN"){
           qDebug() << "This flag does not exist: " << flagName << " in HeaderUtil::getTCPFlag";
    }
    return returnString;
}

QString HeaderUtil::getIPAddress(const Package &data, bool src){
    //Getting the IP Header
    Header header;
    try{
           header = getHeaderByType(HeaderType::IP, data);
    }
    catch(HeaderNotFoundException hnfe){
           qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getIPAddress";
    }

    QVector<quint8> attribute;
    //Getting the source or destination address
    if(src){
           try{
            attribute = getHeaderAttributeByName("Source Address", header).getContentAsArray();
           }
           catch(HeaderAttributeNotFoundException hanfe){
            qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
           }
    }
    else{
           try{
            attribute = getHeaderAttributeByName("Destination Address", header).getContentAsArray();
           }
           catch(HeaderAttributeNotFoundException hanfe){
            qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
           }
    }
    //Creating the IP Address
    IPAddress address(attribute);
    return address.getAddressAsDecString();
}

QString HeaderUtil::getIPFlag(const Package &data, const QString &flagName){
    //Getting the IP Header
    Header header;
    try{
           header = getHeaderByType(HeaderType::IP, data);
    }
    catch(HeaderNotFoundException hnfe){
           qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getIPAddress";
    }
    QVector<quint8> attribute;
    //Getting the flags
    try{
           attribute = getHeaderAttributeByName("Flags", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
          qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getIPFlag";
    }

    quint8 flags = attribute[0];
    QString returnString;

    //Checking which flag
    if(flagName=="DF"){
        ((flags >> 1) & 1) != 0 ? returnString = "true" : returnString = "false";
        return returnString;
    }
    if(flagName=="MF"){
        ((flags >> 2) & 1) != 0 ? returnString = "true" : returnString = "false";
        return returnString;
    }
    qDebug() << "This flag does not exist: " << flagName << " in HeaderUtil::getIPFlag";

    return "";
}

QString HeaderUtil::getIPNextProtocol(const Package &data){
    //Getting the IP Header
    Header header;
    try{
        header = getHeaderByType(HeaderType::IP, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getIPAddress";
    }
    QVector<quint8> attribute;
    //Getting the next Protocol
    try{
        attribute = getHeaderAttributeByName("Protocol", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getIPNextProtocol";
    }

    //Returning the right String
    if(attribute[0] == 17){
        return "UDP";
    }
    if(attribute[0] == 6){
        return "TCP";
    }
    if(attribute[0] == 0){
        return "";
    }
    qDebug() << "Cannot find a following Protocol in HeaderUtil::getIPNextProtocol";
    return "";
}

QString HeaderUtil::getMacAddress(const Package &data, bool src){
    //Getting the Ethernet II Header
    Header header;
    try{
        header = getHeaderByType(HeaderType::MAC, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getMacAddress";
    }

    //Getting the MAC Address
    QVector<quint8> attribute;
    if(src){
        try{
            attribute = getHeaderAttributeByName("Source MAC Address", header).getContentAsArray();
        }
        catch(HeaderAttributeNotFoundException hanfe){
            qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getMacAddress";
        }
    }
    else{
        try{
            attribute = getHeaderAttributeByName("Destination MAC Address", header).getContentAsArray();
        }
        catch(HeaderAttributeNotFoundException hanfe){
            qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getMacAddress";
        }
    }

    MACAddress address(attribute);
    return address.getAddressAsString();
}

QString HeaderUtil::getEtherType(const Package &data){
    //Getting the Ethernet II Header
    Header header;
    try{
        header = getHeaderByType(HeaderType::MAC, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getMacAddress";
    }

    QVector<quint8> attribute;
    try{
        attribute = getHeaderAttributeByName("EtherType", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getEtherType";
    }

    quint16 etherType = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];

    if(etherType == 2048){
        return "IPv4";
    }
    if(etherType == 0){
        return "";
    }
    qDebug() << "No corresponding EtherType found in HeaderUtil::getEtherType";
    return "";
}
