#include "tcp.h"
#include "headerAttribute.h"

TCP::TCP()
{

}

//TODO Restlicher Header
void initHeader(int sourcePort, int destinationPort){
    HeaderAttribute srcPort("Source Port",16,sourcePort);
    HeaderAttribute dstPort("Destination Port",16,destinationPort);
}
