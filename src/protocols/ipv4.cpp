#include "headerAttribute.h"
#include "ipv4.h"

void IPv4::initHeader(quint16 id, bool DF, bool MF, quint16 fragmentOffset, quint8 ttl, quint8 protocol, const IPAddress &sourceAddress, const IPAddress &destinationAdress, Package &data)
{
    HeaderAttribute version("Version",4,static_cast<quint8>(4));
    //Will not be used, by default stores values between 5 or 6 we only store 5
    HeaderAttribute IHL("Header Length",4,static_cast<quint8>(5));
    //Will not be used, is always 0 in this project
    HeaderAttribute TOS("Type Of Service", 8,static_cast<quint8>(0));

    quint16 totalLength = data.getLength() + 20;
    HeaderAttribute length("Total Length",16,totalLength);

    HeaderAttribute identification("Identification", 16, id);

    quint8 flagsVal = 0b00000000;
    setFlag(&flagsVal, DF, 1);
    setFlag(&flagsVal, MF, 2);
    HeaderAttribute flags("Flags", 3, flagsVal);

    HeaderAttribute fragOffset("Fragment Offset", 16, fragmentOffset);
    HeaderAttribute timeToLive("Time To Live", 8, ttl);
    HeaderAttribute nextProtocol("Protocol", 8, protocol);

    HeaderAttribute checksum("Checksum", 16, static_cast<quint16>(getIPv4Checksum(
                                                 totalLength,
                                                 id,
                                                 flagsVal,
                                                 fragmentOffset,
                                                 ttl,
                                                 protocol,
                                                 sourceAddress.getAddressAsArray(),
                                                 destinationAdress.getAddressAsArray(),
                                                 data.getContent().toLatin1().constData(),
                                                                           totalLength)));

    HeaderAttribute srcAdress("Source Address", 32, sourceAddress.getAddressAsArray());
    HeaderAttribute destAdress("Destination Address", 32, destinationAdress.getAddressAsArray());

    //The Options field is always 0, we do not provide options in IPv4 in this project
    HeaderAttribute options("Options", 0, static_cast<quint8>(0));

    Header ipHeader;
    ipHeader.setHeaderType(HeaderType::IP);
    ipHeader.addHeaderAttribute(version);
    ipHeader.addHeaderAttribute(IHL);
    ipHeader.addHeaderAttribute(TOS);
    ipHeader.addHeaderAttribute(length);
    ipHeader.addHeaderAttribute(identification);
    ipHeader.addHeaderAttribute(flags);
    ipHeader.addHeaderAttribute(fragOffset);
    ipHeader.addHeaderAttribute(timeToLive);
    ipHeader.addHeaderAttribute(nextProtocol);
    ipHeader.addHeaderAttribute(checksum);
    ipHeader.addHeaderAttribute(srcAdress);
    ipHeader.addHeaderAttribute(destAdress);

    data.addHeader(ipHeader);
}

void IPv4::setFlag(quint8* flags, bool set, quint8 position){
    if (set) {
        // sets the bit at position
        *flags |= (1 << position);
    } else {
        // deletes the bit at position
        *flags &= ~(1 << position);
    }
}

quint16 IPv4::getIPv4Checksum(quint16 totalLength, quint16 id, quint8 flags, quint16 fragOffset, quint8 ttl, quint8 protocol, const QVector<quint8> &srcAddress, const QVector<quint8> &destAddress, const char* data, quint16 dataLength)
{
    quint32 checksum = 0;

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
    quint16 sourceIPAdressPart1 = (srcAddress[0] << 8) | (srcAddress[1] & 0xFF);
    quint16 sourceIPAdressPart2 = (srcAddress[2] << 8) | (srcAddress[3] & 0xFF);

    // Splitting the destination IP-Address into 2 16-bit parts with correct byte order
    quint16 destinationIPAdressPart1 = (destAddress[0] << 8) | (destAddress[1] & 0xFF);
    quint16 destinationIPAdressPart2 = (destAddress[2] << 8) | (destAddress[3] & 0xFF);

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

    //Adding the Payload Data
    for (auto i = 0; i < dataLength; i += 2) {
        quint16 dataWord = (data[i] << 8) | (data[i + 1] & 0xFF);
        checksum += dataWord;
        if (checksum >> 16)
            checksum = (checksum & 0xFFFF) + (checksum >> 16);
    }

     quint16 finalChecksum = static_cast<quint16>(~checksum); //Converting back to qint16 -> Checksum is 16Bit in IPv4

    return ~finalChecksum;
}

