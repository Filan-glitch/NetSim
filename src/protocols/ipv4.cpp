#include "headerAttribute.h"
#include "ipv4.h"
#include "qdebug.h"

void IPv4::initHeader(qint16 id, bool DF, bool MF, qint16 fragmentOffset, qint8 ttl, qint8 protocol, const IPAddress &sourceAddress, const IPAddress &destinationAdress, Package& data)
{
    HeaderAttribute version("Version",4,4);
    //Will not be used, by default stores values between 5 or 6 we only store 5
    HeaderAttribute IHL("Internet Header Length",4,5);
    //Will not be used, is always 0 in this project
    HeaderAttribute TOS("Type of Service",8,0);

    qint16 totalLength = data.getData().length() + 20;
    HeaderAttribute length("Total Length",16,totalLength);

    HeaderAttribute identification("Identification", 16, id);

    qint8 flagsVal = 0b00000000;
    setFlag(&flagsVal, DF, 1);
    setFlag(&flagsVal, MF, 2);
    HeaderAttribute flags("Flags", 3, flagsVal);

    HeaderAttribute fragOffset("Fragment Offset", 16, fragmentOffset);
    HeaderAttribute timeToLive("Time to live", 8, ttl);
    HeaderAttribute nextProtocol("Protocol", 8, protocol);

    HeaderAttribute checksum("Checksum", 16, getIPv4Checksum(
                                                 totalLength,
                                                 id,
                                                 flagsVal,
                                                 fragmentOffset,
                                                 ttl,
                                                 protocol,
                                                 sourceAddress.getAddressAsArray(),
                                                 destinationAdress.getAddressAsArray(),
                                                 data.getData().toStdString().c_str(),
                                                 totalLength));

    HeaderAttribute srcAdress("Source Adress", 32, sourceAddress.getAddressAsInt());
    HeaderAttribute destAdress("Destination Adress", 32, destinationAdress.getAddressAsInt());

    //The Options field is always 0, we do not provide options in IPv4 in this project
    HeaderAttribute options("Options", 0,0);

    Header ipHeader;
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

QList<Package> IPv4::fragmentPackage(const Package &package, qint32 mtu)
{
    QList<Package> returnList = QList<Package>();
    auto packageAmount = package.getData().size()/mtu + 1;
    auto data = package.getData();
    for(auto i = 0; i < packageAmount; i++) {
        //Daten aufsplitten
        if(i != packageAmount - 1) {
            auto packageFragment = Package(data.first(1500));
            data = data.last(data.size() - 1500);
        } else {
            auto package = Package(data);
        }

        returnList.append(package);

    }
}

void IPv4::setFlag(qint8* flags, bool set, qint8 position){
    if (set) {
        // sets the bit at position
        *flags |= (1 << position);
    } else {
        // deletes the bit at position
        *flags &= ~(1 << position);
    }
}

qint16 IPv4::getIPv4Checksum(qint16 totalLength, qint16 id, qint8 flags, qint16 fragOffset, qint8 ttl, qint8 protocol, qint8* srcAddress, qint8* destAddress, const char* data, qint16 dataLength)
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

    //Adding the Payload Data
    for (int i = 0; i < dataLength; i += 2) {
        qint16 dataWord = (data[i] << 8) | (data[i + 1] & 0xFF);
        checksum += dataWord;
        if (checksum >> 16)
            checksum = (checksum & 0xFFFF) + (checksum >> 16);
    }

     qint16 finalChecksum = static_cast<qint16>(~checksum); //Converting back to qint16 -> Checksum is 16Bit in IPv4

    qInfo() << "IPv4 Checksum: " << ~finalChecksum;
    return ~finalChecksum;
}

