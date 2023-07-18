#include "tcp.h"
#include "headerAttribute.h"
#include "qdebug.h"


void TCP::initHeader(IPAddress srcAdress, IPAddress destAdress, Port sourcePort, Port destinationPort, qint32 seqNumber, qint32 ackNumber, bool ack,bool rst, bool syn, bool fin, qint16 window,Package data,qint16 dataLength){
    HeaderAttribute srcPort("Source Port",16,sourcePort.getPortNumber());
    HeaderAttribute dstPort("Destination Port",16,destinationPort.getPortNumber());
    HeaderAttribute sequenceNumber("Sequence number",32,seqNumber);
    HeaderAttribute acknowledgementNumber("Acknowledgment number",32,ackNumber);

    //Sets the flags for the TCP Header Urgent and Push flag are always 0
    qint16 flags = 0x0000000000000000;
    setFlag(&flags,ack,11);
    setFlag(&flags,rst,13);
    setFlag(&flags,syn,14);
    setFlag(&flags,fin,15);

    //Data-Offset is always 0, because we don't use the options TCP provides in this project
    HeaderAttribute flag("Flags",16,flags);
    HeaderAttribute windowSize("window",16,window);

    HeaderAttribute checksum("TCP Checksum",16,
                             getTCPChecksum(srcAdress.getAddressAsArray(),
                                            destAdress.getAddressAsArray(),
                                            sourcePort.getPortNumber(),
                                            destinationPort.getPortNumber(),
                                            seqNumber,
                                            ackNumber,
                                            flags,
                                            data.getData(),
                                            dataLength));

    //The urgent pointer is always 0 in our case
    qint16 urgend_pointer = 0b0000000000000000;
    HeaderAttribute urgentPointer("Urgent Pointer",16,urgend_pointer);
    HeaderAttribute options("Options",0,0);

    //TODO DATA

}


void TCP::setFlag(qint16* flags, bool set, qint16 position){
    if (set) {
        // sets the bit at position
        *flags |= (1 << position);
    } else {
        // deletes the bit at position
        *flags &= ~(1 << position);
    }
}

qint16 TCP::getTCPChecksum(qint8* sourceAddress, qint8* destinationAddress, qint16 sourcePort, qint16 destinationPort, qint32 seqNumber, qint32 ackNumber, qint16 flags,const char* data, qint16 dataLength) {
    // TCP Pseudo Header
    qint32 pseudoHeader = 0;

    // Splitting the source IP-Address into 2 16-bit parts with correct byte order
    qint16 sourceIPAdressPart1 = (sourceAddress[0] << 8) | (sourceAddress[1] & 0xFF);
    qint16 sourceIPAdressPart2 = (sourceAddress[2] << 8) | (sourceAddress[3] & 0xFF);

    // Splitting the destination IP-Address into 2 16-bit parts with correct byte order
    qint16 destinationIPAdressPart1 = (destinationAddress[0] << 8) | (destinationAddress[1] & 0xFF);
    qint16 destinationIPAdressPart2 = (destinationAddress[2] << 8) | (destinationAddress[3] & 0xFF);

    pseudoHeader += sourceIPAdressPart1;
    pseudoHeader += sourceIPAdressPart2;
    pseudoHeader += destinationIPAdressPart1;
    pseudoHeader += destinationIPAdressPart2;
    pseudoHeader += 6; // IP protocol field for TCP is 6
    pseudoHeader += dataLength;

    qint16 checksum = 0;
    //Adding the pseudo Header to the checksum and handling the possible overflow
    while (pseudoHeader >> 16){
        pseudoHeader = (pseudoHeader & 0xFFFF) + (pseudoHeader >> 16);
    }
    checksum += pseudoHeader;

    //Adding the TCP-Header data
    checksum += sourcePort;
    checksum += destinationPort;
    checksum += seqNumber;
    checksum += ackNumber;
    checksum += flags;

    //Adding the TCP Data
    for (int i = 0; i < dataLength; i += 2) {
        qint16 dataWord = (data[i] << 8) | (data[i + 1] & 0xFF);
        checksum += dataWord;
        if (checksum >> 16)
            checksum = (checksum & 0xFFFF) + (checksum >> 16);
    }

    qInfo() << "TCP Checksum: " << ~checksum;
    return ~checksum;
}
