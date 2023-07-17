#include "tcp.h"
#include "headerAttribute.h"

TCP::TCP()
{

}

//TODO Data-Offset, Checksum, Options
void TCP::initHeader(int sourcePort, int destinationPort, int seqNumber, int ackNumber, bool ack,bool rst, bool syn, bool fin, int window){
    HeaderAttribute srcPort("Source Port",16,sourcePort);
    HeaderAttribute dstPort("Destination Port",16,destinationPort);
    HeaderAttribute sequenceNumber("Sequence number",32,seqNumber);
    HeaderAttribute acknowledgementNumber("Acknowledgment number",32,ackNumber);

    //Sets the flags for the TCP Header Urgent and Push flag are always 0
    uint16_t flags = 0x0000000000000000;
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
    uint16_t urgend_pointer = 0x0000000000000000;
    HeaderAttribute urgentPointer("Urgent Pointer",16,urgend_pointer);

    //TODO Options

}


void TCP::setFlag(uint16_t* flags, bool set, int position){
    if (set) {
        // sets the bit at position
        *flags |= (1 << position);
    } else {
        // deletes the bit at position
        *flags &= ~(1 << position);
    }
}
