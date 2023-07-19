#include "udp.h"
#include "headerAttribute.h"

#include <QDebug>

void UDP::initHeader(const Port &sourcePort, const Port &destinationPort, qint16 dataLength, Package& data){
    HeaderAttribute srcPort("Source Port",16,sourcePort.getPortNumber());
    HeaderAttribute dstPort("Destination Port",16,destinationPort.getPortNumber());
    HeaderAttribute length("length",16,dataLength);
    HeaderAttribute checksum("checksum",16,getChecksum(data.getData().toStdString().c_str(),dataLength,sourcePort.getPortNumber(),destinationPort.getPortNumber()));

    Header udpHeader;
    udpHeader.addHeaderAttribute(srcPort);
    udpHeader.addHeaderAttribute(dstPort);
    udpHeader.addHeaderAttribute(length);
    udpHeader.addHeaderAttribute(checksum);

    data.addHeader(udpHeader);
}

qint16 UDP::overflowHandling(qint16 checksum){
    if(checksum >> 16){
        checksum = (checksum & 0xFFFF) + 1;
    }
    return checksum;
}

qint16 UDP::getChecksum(const char* data, qint16 length, qint16 sourcePort, qint16 destinationPort){
    qint16 checksum = 0;

    checksum += sourcePort;
    checksum += destinationPort;

    //Overflow handling
    checksum = overflowHandling(checksum);

    checksum += static_cast<qint16>(length);

    //Overflow handling
    checksum = overflowHandling(checksum);

    for(qint16 i = 0; i < length; i+=2){
        //Combining to 16 Bit words
        qint16 word = (data[i] << 8) | data[i+1];
        checksum += word;

        //Overflow handling
        checksum = overflowHandling(checksum);
    }

    //In case data length is uneven
    if(length % 2 != 0){
        //adds the 0 Byte
        qint16 lastWord = (data[length-1] << 8) | 0x00;
        checksum += lastWord;

        //Overflow handling
        checksum = overflowHandling(checksum);
    }

    //Returns the inverse
    qInfo() << "UDP Checksum: " << ~checksum;
    return ~checksum;
}
