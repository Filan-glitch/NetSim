#include "Headernotfoundexception.h"
#include "headerattributenotfoundexception.h"
#include "headerutil.h"
#include "src/models/dnsentry.h"
#include "src/models/ipaddress.h"
#include "src/models/macaddress.cpp"
#include <QDebug>

// Ethernet

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

// IP

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

QString HeaderUtil::getIPHeaderLength(const Package &data) {
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
        attribute = getHeaderAttributeByName("Header Length", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getIPNextProtocol";
    }

    return QString::number(attribute[0]);
}

QString HeaderUtil::getIPTOS(const Package &data) {
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
        attribute = getHeaderAttributeByName("Type Of Service", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getIPNextProtocol";
    }

    return QString("0x") + QString::number(attribute[0], 16);
}

QString HeaderUtil::getIPTotalLength(const Package &data) {
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
        attribute = getHeaderAttributeByName("Total Length", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getIPNextProtocol";
    }

    quint16 length = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];

    return QString::number(length);
}

QString HeaderUtil::getIPIdentification(const Package &data) {
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
        attribute = getHeaderAttributeByName("Identification", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getIPNextProtocol";
    }

    quint16 id = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];

    return QString("0x") + QString::number(id, 16);
}

QString HeaderUtil::getIPTTL(const Package &data) {
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
        attribute = getHeaderAttributeByName("Time To Live", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getIPNextProtocol";
    }

    return QString::number(attribute[0]);
}

QString HeaderUtil::getIPChecksum(const Package& data) {
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
        attribute = getHeaderAttributeByName("Checksum", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getIPNextProtocol";
    }

    quint16 checksum = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];

    return QString("0x") + QString::number(checksum, 16).toUpper();
}

QString HeaderUtil::getIPFragmentOffset(const Package& data) {
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
        attribute = getHeaderAttributeByName("Fragment Offset", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getIPNextProtocol";
    }

    quint16 offset = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];

    return QString::number(offset);
}

// TCP

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

    //checking ack flag
    if(flagName == "ACK"){
        ((flag >> 4) & 1) != 0 ? returnString = "true" : returnString = "false";
    }
    //checking rst flag
    if(flagName == "RST"){
        ((flag >> 2) & 1) != 0 ? returnString = "true" : returnString = "false";
    }
    //checking syn flag
    if(flagName == "SYN"){
        ((flag >> 1) & 1) != 0 ? returnString = "true" : returnString = "false";
    }
    //checking fin flag
    if(flagName == "FIN"){
        (flag & 1) != 0 ? returnString = "true" : returnString = "false";
    }
    if(flagName != "ACK" && flagName !="RST" && flagName !="SYN" && flagName != "FIN"){
        qDebug() << "This flag does not exist: " << flagName << " in HeaderUtil::getTCPFlag";
    }
    return returnString;
}

QString HeaderUtil::getTCPSequenceNumber(const Package &data) {
    //Get header
    Header header;
    try{
        header = getHeaderByType(HeaderType::TCP, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
    }

    //Get attribute
    QVector<quint8> attribute;
    try{
        attribute = getHeaderAttributeByName("Sequence Number", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
    }

    quint32 sequenceNumber = attribute[0] << 24 | attribute[1] << 16 | attribute[2] << 8 | attribute[3];
    return QString::number(sequenceNumber);
}

QString HeaderUtil::getTCPAcknowledgementNumber(const Package &data) {
    //Get header
    Header header;
    try{
        header = getHeaderByType(HeaderType::TCP, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
    }

    //Get attribute
    QVector<quint8> attribute;
    try{
        attribute = getHeaderAttributeByName("Acknowledgment Number", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
    }

    quint32 sequenceNumber = attribute[0] << 24 | attribute[1] << 16 | attribute[2] << 8 | attribute[3];
    return QString::number(sequenceNumber);

}

QString HeaderUtil::getTCPHeaderLength(const Package &data) {
    //Get header
    Header header;
    try{
        header = getHeaderByType(HeaderType::TCP, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
    }

    //Get attribute
    QVector<quint8> attribute;
    try{
        attribute = getHeaderAttributeByName("Header Length", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
    }

    return QString::number(attribute[0]);
}

QString HeaderUtil::getTCPWindow(const Package &data) {
    //Get header
    Header header;
    try{
        header = getHeaderByType(HeaderType::TCP, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
    }

    //Get attribute
    QVector<quint8> attribute;
    try{
        attribute = getHeaderAttributeByName("Window", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getTCPFlag";
    }

    quint16 sequenceNumber = attribute[0] << 8 | attribute[1];
    return QString::number(sequenceNumber);
}

QString HeaderUtil::getTCPChecksum(const Package &data) {
    Header header;
    try {
        header = getHeaderByType(HeaderType::TCP, data);
    } catch (HeaderNotFoundException hnfe) {
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getTCPChecksum";
    }

    //Get attribute
    QVector<quint8> attribute;
    try {
        attribute = getHeaderAttributeByName("Checksum", header).getContentAsArray();
    } catch (HeaderAttributeNotFoundException hanfe) {
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getTCPChecksum";
    }

    quint16 checksum = attribute[0] << 8 | attribute[1];
    return QString("0x") + QString::number(checksum, 16).toUpper();
}

QString HeaderUtil::getTCPUrgentPointer(const Package &data) {
    Header header;
    try {
        header = getHeaderByType(HeaderType::TCP, data);
    } catch (HeaderNotFoundException hnfe) {
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getTCPUrgentPointer";
    }

    //Get attribute
    QVector<quint8> attribute;
    try {
        attribute = getHeaderAttributeByName("Urgent Pointer", header).getContentAsArray();
    } catch (HeaderAttributeNotFoundException hanfe) {
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getTCPUrgentPointer";
    }

    quint16 urgentPointer = attribute[0] << 8 | attribute[1];
    return QString::number(urgentPointer);
}

// UDP

QString HeaderUtil::getUDPChecksum(const Package &data) {
    Header header;
    try {
        header = getHeaderByType(HeaderType::UDP, data);
    } catch (HeaderNotFoundException hnfe) {
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getUDPChecksum";
    }

    QVector<quint8> attribute;
    try {
        attribute = getHeaderAttributeByName("Checksum", header).getContentAsArray();
    } catch (HeaderAttributeNotFoundException hanfe) {
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getUDPChecksum";
    }

    quint16 checksum = attribute[0] << 8 | attribute[1];

    return QString("0x") + QString::number(checksum, 16).toUpper();
}

QString HeaderUtil::getUDPLength(const Package &data) {
    Header header;
    try {
        header = getHeaderByType(HeaderType::UDP, data);
    } catch (HeaderNotFoundException hnfe) {
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getUDPLength";
    }

    QVector<quint8> attribute;
    try {
        attribute = getHeaderAttributeByName("Length", header).getContentAsArray();
    } catch (HeaderAttributeNotFoundException hanfe) {
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getUDPLength";
    }

    quint16 length = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];

    return QString::number(length);
}

// HTTP

QString HeaderUtil::getHTTPAttribute(const Package &data, const QString &attributeName){
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

// DNS

QString HeaderUtil::getDNSID(const Package &data)
{
    Header header;
    try{
        header = getHeaderByType(HeaderType::DNS, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getDNSID";
    }

    QVector<quint8> attribute;
    try{
        attribute = getHeaderAttributeByName("Transaction ID", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getDNSID";
    }

    quint16 dnsID = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];

    return QString("0x") + QString::number(dnsID, 16).toUpper();
}

QString HeaderUtil::getDNSFlag(const Package &data)
{
    Header header;
    try{
        header = getHeaderByType(HeaderType::DNS, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getDNSFlag";
    }

    QVector<quint8> attribute;
    try{
        attribute = getHeaderAttributeByName("Flags", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getDNSFlag";
    }

    quint16 dnsFlag = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];

    return QString("0b") + QString::number(dnsFlag, 2).rightJustified(16, '0');
}

QString HeaderUtil::getDNSQuestions(const Package &data)
{
    Header header;
    try{
        header = getHeaderByType(HeaderType::DNS, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    QVector<quint8> attribute;
    quint16 dnsQuestions = 0;
    try{
        attribute = getHeaderAttributeByName("Questions", header).getContentAsArray();
        dnsQuestions = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    return QString::number(dnsQuestions);
}

QString HeaderUtil::getDNSAnswerRRs(const Package &data)
{
    Header header;
    try{
        header = getHeaderByType(HeaderType::DNS, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    QVector<quint8> attribute;
    try{
        attribute = getHeaderAttributeByName("Answer RRs", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    quint16 dnsAnswers = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];

    return QString::number(dnsAnswers);
}

QString HeaderUtil::getDNSAuthorityRRs(const Package &data)
{
    Header header;
    try{
        header = getHeaderByType(HeaderType::DNS, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    QVector<quint8> attribute;
    try{
        attribute = getHeaderAttributeByName("Authority RRs", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    quint16 dnsAuthority = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];

    return QString::number(dnsAuthority);
}

QString HeaderUtil::getDNSAdditionalRRs(const Package &data)
{
    Header header;
    try{
        header = getHeaderByType(HeaderType::DNS, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    QVector<quint8> attribute;
    try{
        attribute = getHeaderAttributeByName("Additional RRs", header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    quint16 dnsAdditional = (static_cast<quint16>(attribute[0]) << 8) + attribute[1];

    return QString::number(dnsAdditional);
}

QString HeaderUtil::getDNSQuery(const Package &data, int index)
{
    Header header;
    try{
        header = getHeaderByType(HeaderType::DNS, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    QVector<quint8> attribute;
    try{
        attribute = getHeaderAttributeByName("Query " + QString::number(index), header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    return QString();
}

QString HeaderUtil::getDNSAnswer(const Package &data, int index)
{
    Header header;
    try{
        header = getHeaderByType(HeaderType::DNS, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    QVector<quint8> attribute;
    try{
        attribute = getHeaderAttributeByName("Answer " + QString::number(index), header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    return QString();
}

QString HeaderUtil::getDNSAuthoritativeNameserver(const Package &data, int index)
{
    Header header;
    try{
        header = getHeaderByType(HeaderType::DNS, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    QVector<quint8> attribute;
    try{
        attribute = getHeaderAttributeByName("Authoritative Nameserver " + QString::number(index), header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    return QString();
}

QString HeaderUtil::getDNSAdditionalRecord(const Package &data, int index)
{
    Header header;
    try{
        header = getHeaderByType(HeaderType::DNS, data);
    }
    catch(HeaderNotFoundException hnfe){
        qDebug() << hnfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    QVector<quint8> attribute;
    try{
        attribute = getHeaderAttributeByName("Additional Record " + QString::number(index), header).getContentAsArray();
    }
    catch(HeaderAttributeNotFoundException hanfe){
        qDebug() << hanfe.getErrorMessage() << " in HeaderUtil::getDNSQuestions";
    }

    return QString();
}

// Allrounder

QString HeaderUtil::getPackageLength(const Package &package) {
    return QString::number(package.getLength());
}

HeaderType HeaderUtil::getApplicationProtocol(const Package &data){
    if (data.getHeaders().size() < 4) {
        return HeaderType::UNKNOWN;
    }
    if (data.getHeaders().at(0).getType() == HeaderType::HTTP) {
        return HeaderType::HTTP;
    } else {
        return HeaderType::DNS;
    }
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
