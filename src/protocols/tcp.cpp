#include "tcp.h"
#include "headerAttribute.h"


//TODO Data-Offset, Checksum, Options
void TCP::initHeader(Port sourcePort, Port destinationPort, qint32 seqNumber, qint32 ackNumber, bool ack,bool rst, bool syn, bool fin, qint16 window){
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

    //TODO Data-Offset calc. At this point it is always 4
    setFlag(&flags,true,0);
    setFlag(&flags,true,1);
    setFlag(&flags,true,2);
    setFlag(&flags,true,3);

    HeaderAttribute flag("Flags",16,flags);
    HeaderAttribute windowSize("window",16,window);

    //TODO Checksum

    //The urgent pointer is always 0 in our case
    qint16 urgend_pointer = 0b0000000000000000;
    HeaderAttribute urgentPointer("Urgent Pointer",16,urgend_pointer);

    //TODO Options

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
