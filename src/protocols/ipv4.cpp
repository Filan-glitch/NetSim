#include "headerAttribute.h"
#include "ipv4.h"
#include "qdebug.h"

void IPv4::initHeader(qint16 id, qint8 flags, qint16 fragmentOffset, qint8 ttl, qint8 protocol, IPAddress sourceAddress, IPAddress destinationAdress, char* data)
{
    HeaderAttribute version("Version",4,4);
    //Will not be used, by default stores values between 5 and 15 we only store 5
    HeaderAttribute IHL("Internet Header Length",4,5);
    //Will not be used, is always 0 in this project
    HeaderAttribute TOS("Type of Service",8,0);

    qint16 totalLength = strlen(data) + 20;
    HeaderAttribute length("Total Length",16,totalLength);

    HeaderAttribute identification("Identification", 16, id);

    //TODO Flags
    HeaderAttribute fragOffset("Fragment Offset", 16, fragmentOffset);
    HeaderAttribute timeToLive("Time to live", 8, ttl);
    HeaderAttribute nextProtocol("Protocol", 8, protocol);

    HeaderAttribute checksum("Checksum", 16, getIPv4Checksum(
                                                 totalLength,
                                                 id,
                                                 flags,
                                                 fragmentOffset,
                                                 ttl,
                                                 protocol,
                                                 sourceAddress.getAddressAsArray(),
                                                             destinationAdress.getAddressAsArray()));

    HeaderAttribute srcAdress("Source Adress", 32, sourceAddress);
    HeaderAttribute destAdress("Destination Adress", 32, destinationAdress);

    //The Options field is always 0, we do not provide options in IPv4 in this project
    HeaderAttribute options("Options", 0,0);
    //TODO Data
}

qint16 IPv4::getIPv4Checksum(qint16 totalLength, qint16 id, qint8 flags, qint16 fragOffset, qint8 ttl, qint8 protocol, qint8* srcAddress, qint8* destAddress)
{
    qint32 checksum = 0;

    //Version
    checksum += 4;

    //Internet Header Length
    checksum += 5;

    //TOS
    checksum += 0;

    //Total Length
    checksum += totalLength;
    if (checksum >> 16) { //Overflow handling
        checksum = (checksum & 0xFFFF) + (checksum >> 16);
    }

    //Identification
    checksum += id;
    if (checksum >> 16) { //Overflow handling
        checksum = (checksum & 0xFFFF) + (checksum >> 16);
    }

    //Flags
    checksum += flags;
    if (checksum >> 16) { //Overflow handling
        checksum = (checksum & 0xFFFF) + (checksum >> 16);
    }

    //Fragment Offset
    checksum += fragOffset;
    if (checksum >> 16) { //Overflow handling
        checksum = (checksum & 0xFFFF) + (checksum >> 16);
    }

    //TTL
    checksum += ttl;
    if (checksum >> 16) { //Overflow handling
        checksum = (checksum & 0xFFFF) + (checksum >> 16);
    }

    //Protocol
    checksum += protocol;
    if (checksum >> 16) { //Overflow handling
        checksum = (checksum & 0xFFFF) + (checksum >> 16);
    }

    // Splitting the source IP-Address into 2 16-bit parts with correct byte order
    qint16 sourceIPAdressPart1 = (srcAddress[0] << 8) | (srcAddress[1] & 0xFF);
    qint16 sourceIPAdressPart2 = (srcAddress[2] << 8) | (srcAddress[3] & 0xFF);

    // Splitting the destination IP-Address into 2 16-bit parts with correct byte order
    qint16 destinationIPAdressPart1 = (destAddress[0] << 8) | (destAddress[1] & 0xFF);
    qint16 destinationIPAdressPart2 = (destAddress[2] << 8) | (destAddress[3] & 0xFF);

    //Source IP Address
    checksum += sourceIPAdressPart1;
    if (checksum >> 16) { //Overflow handling
        checksum = (checksum & 0xFFFF) + (checksum >> 16);
    }
    checksum += sourceIPAdressPart2;
    if (checksum >> 16) { //Overflow handling
        checksum = (checksum & 0xFFFF) + (checksum >> 16);
    }

    //Destination IP Address
    checksum += destinationIPAdressPart1;
    if (checksum >> 16) { //Overflow handling
        checksum = (checksum & 0xFFFF) + (checksum >> 16);
    }
    checksum += destinationIPAdressPart2;
    if (checksum >> 16) { //Overflow handling
        checksum = (checksum & 0xFFFF) + (checksum >> 16);
    }

     qint16 finalChecksum = static_cast<qint16>(~checksum); //Converting back to qint16 -> Checksum is 16Bit in IPv4

    qInfo() << "IPv4 Checksum: " << ~finalChecksum;
    return ~finalChecksum;
}

