#include "udp.h"
#include "headerAttribute.h"

#include <QDebug>

UDP::UDP()
{

}

void UDP::initHeader(int sourcePort, int destinationPort,size_t dataLength, char* data){
    HeaderAttribute srcPort("Source Port",16,sourcePort);
    HeaderAttribute dstPort("Destination Port",16,destinationPort);
    HeaderAttribute length("length",16,dataLength);
    HeaderAttribute checksum("checksum",16,getChecksum(data,dataLength,sourcePort,destinationPort));
}

int UDP::overflowHandling(int checksum){
    if(checksum >> 16){
        checksum = (checksum & 0xFFFF) + 1;
    }
    return checksum;
}

int UDP::getChecksum(char* data, size_t length, int sourcePort, int destinationPort){
    int checksum = 0;

    checksum += static_cast<uint16_t>(sourcePort);
    checksum += static_cast<uint16_t>(destinationPort);

    //Overflow handling
    checksum = overflowHandling(checksum);

    checksum += static_cast<uint16_t>(length);

    //Overflow handling
    checksum = overflowHandling(checksum);

    for(size_t i = 0; i < length; i+=2){
        //Combining to 16 Bit words
        uint16_t word = (data[i] << 8) | data[i+1];
        checksum += word;

        //Overflow handling
        checksum = overflowHandling(checksum);
    }

    //In case data length is uneven
    if(length % 2 != 0){
        //adds the 0 Byte
        uint16_t lastWord = (data[length-1] << 8) | 0x00;
        checksum += lastWord;

        //Overflow handling
        checksum = overflowHandling(checksum);
    }

    //Returns the inverse
    qDebug() << "Checksum: " << ~checksum;
    return ~checksum;
}
