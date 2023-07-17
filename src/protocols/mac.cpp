#include "headerAttribute.h"
#include "mac.h"

MAC::MAC()
{

}

void MAC::initHeader(qint8* destMACAdress, qint8* srcMACAdress, qint16 lengthField){
    qint64 pre = 0b10101010101010101010101010101010101010101010101010101010101010;
    HeaderAttribute preamble("Preamble", 64, pre);
    qint64 frameDelimiter = 0b10101011;
    HeaderAttribute sfd("Start Frame Delimiter", 8, frameDelimiter);
    HeaderAttribute destinationMacAdress("Destination MAC Adress", 48, destMACAdress);
    HeaderAttribute sourceMacAdress("Source MAC Adress", 48, srcMACAdress);
    HeaderAttribute length("Length Field", 16, lengthField);

    //TODO FRAME CHECK SEQUENCE
}
