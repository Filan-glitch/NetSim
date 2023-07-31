#include "headerAttribute.h"
#include "mac.h"

void MAC::initHeader(Package& data, const MACAddress &destMACAddress, const MACAddress &srcMACAddress, quint16 lengthField){
    quint64 pre = 0b10101010'10101010'10101010'10101010'10101010'10101010'10101010;
    HeaderAttribute preamble("Preamble", 56, pre);
    quint8 frameDelimiter = 0b10101011;
    HeaderAttribute sfd("Start Frame Delimiter", 8, frameDelimiter);
    HeaderAttribute destinationMacAddress("Destination MAC Adress", 48, destMACAddress.getAddressAsInt());
    HeaderAttribute sourceMacAddress("Source MAC Adress", 48, srcMACAddress.getAddressAsInt());
    HeaderAttribute length("Length Field", 16, lengthField);

    //TODO FRAME CHECK SEQUENCE
    Header* macHeader = new Header();
    macHeader->setHeaderType(HeaderType::MAC);
    macHeader->addHeaderAttribute(preamble);
    macHeader->addHeaderAttribute(sfd);
    macHeader->addHeaderAttribute(destinationMacAddress);
    macHeader->addHeaderAttribute(sourceMacAddress);
    macHeader->addHeaderAttribute(length);
    //TODO ADDING FCS

    data.addHeader(macHeader);
}
