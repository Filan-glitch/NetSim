#include "ethernet2.h"
#include "src/models/header.h"s
#include <QIODevice>

using namespace NetSim;

void Ethernet2::initHeader(Package &data, const MACAddress &destMACAddress,
                     const MACAddress &srcMACAddress, quint16 etherType) {
  QBitArray destinationMacAddress(destMACAddress.toArray());
  QBitArray sourceMacAddress(srcMACAddress.toArray());
  QBitArray eType(etherType);

  Header macHeader;
  macHeader.addHeaderAttribute(destinationMacAddress);
  macHeader.addHeaderAttribute(sourceMacAddress);
  macHeader.addHeaderAttribute(eType);

  data.appendData(macHeader.toData());
}
