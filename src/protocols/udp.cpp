#include "udp.h"
#include "headerAttribute.h"

UDP::UDP()
{

}

//TODO Length und Checksum Berechnung
void initHeader(int sourcePort, int destinationPort){
    HeaderAttribute srcPort("Source Port",16,sourcePort);
    HeaderAttribute dstPort("Destination Port",16,destinationPort);
}
