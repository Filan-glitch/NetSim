#include "headerAttribute.h"
#include "ipv4.h"

void IPv4::initHeader(qint16 id, qint8 flags, qint16 fragmentOffset, qint8 ttl, qint8 protocol, qint32 sourceAdress, qint32 destinationAdress, char* options, char* data)
{
    HeaderAttribute version("Version",4,4);
    HeaderAttribute IHL("Internet Header Length",4,5);
    HeaderAttribute TOS("Type of Service",8,0);
    qint16 totalLength = strlen(options) + strlen(data) + 20;
    HeaderAttribute length("Total Length",16,totalLength);
    HeaderAttribute identification("Identification", 16, id);
    //TODO Flags
    HeaderAttribute fragOffset("Fragment Offset", 16, fragmentOffset);
    HeaderAttribute timeToLive("Time to live", 8, ttl);
    HeaderAttribute nextProtocol("Protocol", 8, protocol);
    //TODO Checksum
    HeaderAttribute srcAdress("Source Adress", 32, sourceAdress);
    HeaderAttribute destAdress("Destination Adress", 32, destinationAdress);
    //TODO Options
    //TODO Data
}

