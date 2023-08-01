#include "Headernotfoundexception.h"
#include "headerattributenotfoundexception.h"
#include "headerutil.h"
#include "src/management/logger.h"

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
    if(flagName == "ack"){
           ((flag >> 10) & 1) != 0 ? returnString = "true" : returnString = "false";
    }
    //checking rst flag
    if(flagName == "rst"){
           ((flag >> 12) & 1) != 0 ? returnString = "true" : returnString = "false";
    }
    //checking syn flag
    if(flagName == "syn"){
           ((flag >> 13) & 1) != 0 ? returnString = "true" : returnString = "false";
    }
    //checking fin flag
    if(flagName == "fin"){
           ((flag >> 14) & 1) != 0 ? returnString = "true" : returnString = "false";
    }

    return returnString;
}
