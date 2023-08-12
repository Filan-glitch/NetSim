#include "mac.h"
#include "headerAttribute.h"
#include <QIODevice>

using namespace NetSim;

void MAC::initHeader(Package &data, const MACAddress &destMACAddress,
                     const MACAddress &srcMACAddress, quint16 etherType) {
  quint64 pre =
      0b10101010'10101010'10101010'10101010'10101010'10101010'10101010;
  HeaderAttribute preamble("Preamble", 56, pre);
  quint8 frameDelimiter = 0b10101011;
  HeaderAttribute sfd("Start Frame Delimiter", 8, frameDelimiter);
  HeaderAttribute destinationMacAddress("Destination MAC Address", 48,
                                        destMACAddress.toArray());
  HeaderAttribute sourceMacAddress("Source MAC Address", 48,
                                   srcMACAddress.toArray());
  HeaderAttribute eType("EtherType", 16, etherType);
  HeaderAttribute fcs("Frame Check Sequence", 32,
                      getFCS(destMACAddress, srcMACAddress, etherType, data));

  Header macHeader;
  macHeader.setHeaderType(HeaderType::MAC);
  macHeader.addHeaderAttribute(preamble);
  macHeader.addHeaderAttribute(sfd);
  macHeader.addHeaderAttribute(destinationMacAddress);
  macHeader.addHeaderAttribute(sourceMacAddress);
  macHeader.addHeaderAttribute(eType);
  macHeader.addHeaderAttribute(fcs);

  data.addHeader(macHeader);
}

quint32 MAC::getFCS(const MACAddress &destMACAddress,
                    const MACAddress &srcMACAddress, quint16 etherType,
                    const Package &data) {
  QByteArray frameData;
  QDataStream stream(&frameData, QIODevice::WriteOnly);
  stream << destMACAddress.toInt() << srcMACAddress.toInt() << etherType
         << data.content().toLatin1().constData();

  return calculateCRC32(frameData);
}

quint32 MAC::calculateCRC32(const QByteArray &data) {
  static const quint32 crc32Table[] = {0x00000000, 0x77073096, 0xEE0E612C,
                                       0x990951BA, 0x076DC419, 0x706AF48F,
                                       0xE963A535, 0x9E6495A3};

  quint32 crc = 0xFFFFFFFF;

  for (int i = 0; i < data.size(); ++i) {
    quint8 index = (crc ^ data[i]) & 0xFF;
    crc = crc32Table[index] ^ (crc >> 8);
  }

  return crc ^ 0xFFFFFFFF;
}
