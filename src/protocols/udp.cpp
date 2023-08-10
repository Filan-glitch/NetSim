#include "udp.h"
#include "headerAttribute.h"

#include <QDebug>

void UDP::initHeader(const Port &sourcePort, const Port &destinationPort, Package& data){
    HeaderAttribute srcPort("Source Port",16,sourcePort.getPortNumber());
    HeaderAttribute dstPort("Destination Port",16,destinationPort.getPortNumber());
    HeaderAttribute length("Length",16, static_cast<quint16>(data.getContent().length() + 8));
    HeaderAttribute checksum("Checksum",16,getChecksum(data.getContent().toLatin1().constData(), data.getContent().length() + 8,sourcePort.getPortNumber(),destinationPort.getPortNumber()));

    Header udpHeader;
    udpHeader.setHeaderType(HeaderType::UDP);
    udpHeader.addHeaderAttribute(srcPort);
    udpHeader.addHeaderAttribute(dstPort);
    udpHeader.addHeaderAttribute(length);
    udpHeader.addHeaderAttribute(checksum);

    data.addHeader(udpHeader);
}

quint16 UDP::overflowHandling(quint16 checksum){
    if(checksum >> 16){
        checksum = (checksum & 0xFFFF) + 1;
    }
    return checksum;
}

quint16 UDP::getChecksum(const char* data, quint16 length, quint16 sourcePort, quint16 destinationPort){
    quint16 checksum = 0;

    checksum += sourcePort;
    checksum += destinationPort;

    //Overflow handling
    checksum = overflowHandling(checksum);

    checksum += static_cast<quint16>(length);

    //Overflow handling
    checksum = overflowHandling(checksum);

    for(quint16 i = 0; i < length; i+=2){
        //Combining to 16 Bit words
        quint16 word = (data[i] << 8) | data[i+1];
        checksum += word;

        //Overflow handling
        checksum = overflowHandling(checksum);
    }

    //In case data length is uneven
    if(length % 2 != 0){
        //adds the 0 Byte
        quint16 lastWord = (data[length-1] << 8) | 0x00;
        checksum += lastWord;

        //Overflow handling
        checksum = overflowHandling(checksum);
    }

    //Returns the inverse
    return ~checksum;
}
