#include "headerAttribute.h"
#include "mac.h"

void MAC::initHeader(Package data, MACAddress destMACAddress, MACAddress srcMACAddress, qint16 lengthField){
    qint64 pre = 0b10101010'10101010'10101010'10101010'10101010'10101010'10101010;
    HeaderAttribute preamble("Preamble", 56, pre);
    qint8 frameDelimiter = 0b10101011;
    HeaderAttribute sfd("Start Frame Delimiter", 8, frameDelimiter);
    HeaderAttribute destinationMacAddress("Destination MAC Adress", 48, destMACAddress.getAddressAsInt());
    HeaderAttribute sourceMacAddress("Source MAC Adress", 48, srcMACAddress.getAddressAsInt());
    HeaderAttribute length("Length Field", 16, lengthField);

    //TODO FRAME CHECK SEQUENCE
    //TODO DATA
}
