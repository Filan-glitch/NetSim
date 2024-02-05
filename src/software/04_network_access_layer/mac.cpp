#include "mac.h"
#include "src/software/00_common/headerAttribute.h"
#include <QIODevice>

using namespace NetSim;

void MAC::initHeader(Package &data, const MACAddress &destMACAddress,
                     const MACAddress &srcMACAddress, quint16 etherType) {
  HeaderAttribute destinationMacAddress("Destination MAC Address", 48,
                                        destMACAddress.toArray());
  HeaderAttribute sourceMacAddress("Source MAC Address", 48,
                                   srcMACAddress.toArray());
  HeaderAttribute eType("EtherType", 16, etherType);

  Header macHeader;
  macHeader.setHeaderType(HeaderType::MAC);
  macHeader.addHeaderAttribute(destinationMacAddress);
  macHeader.addHeaderAttribute(sourceMacAddress);
  macHeader.addHeaderAttribute(eType);

  data.addHeader(macHeader);
}
