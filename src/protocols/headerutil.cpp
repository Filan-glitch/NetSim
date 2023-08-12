#include "headerutil.h"
#include "Headernotfoundexception.h"
#include "headerattributenotfoundexception.h"
#include "src/models/ipaddress.h"
#include "src/models/macaddress.h"
#include <QDebug>
#include <QException>

using namespace NetSim;

// Ethernet

QString HeaderUtil::getMacAddress(const Package &data, bool src) {
  // Getting the Ethernet II Header
  Header header;
  try {
    header = data[HeaderType::MAC];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getMacAddress";
    return "";
  }

  // Getting the MAC Address
  QVector<quint8> attribute;
  if (src) {
    try {
      attribute = header["Source MAC Address"].toArray();
    } catch (const HeaderAttributeNotFoundException &hanfe) {
      qDebug() << hanfe.errorMessage() << " in HeaderUtil::getMacAddress";
      return "";
    }
  } else {
    try {
      attribute = header["Destination MAC Address"].toArray();
    } catch (const HeaderAttributeNotFoundException &hanfe) {
      qDebug() << hanfe.errorMessage() << " in HeaderUtil::getMacAddress";
      return "";
    }
  }

  MACAddress address(attribute);
  return address.toString();
}

QString HeaderUtil::getEtherType(const Package &data) {
  // Getting the Ethernet II Header
  Header header;
  try {
    header = data[HeaderType::MAC];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getMacAddress";
    return "";
  }

  QVector<quint8> attribute;
  try {
    attribute = header["EtherType"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getEtherType";
    return "";
  }

  quint16 etherType = attribute[0] << 8 | attribute[1];

  if (etherType == 2048) {
    return "IPv4";
  }
  if (etherType == 0) {
    return "";
  }
  qDebug() << "No corresponding EtherType found in HeaderUtil::getEtherType";
  return "";
}

// IP

QString HeaderUtil::getIPAddress(const Package &data, bool src) {
  // Getting the IP Header
  Header header;
  try {
    header = data[HeaderType::IP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getIPAddress";
    return "";
  }

  QVector<quint8> attribute;
  // Getting the source or destination address
  if (src) {
    try {
      attribute = header["Source Address"].toArray();
    } catch (const HeaderAttributeNotFoundException &hanfe) {
      qDebug() << hanfe.errorMessage() << " in HeaderUtil::getTCPFlag";
      return "";
    }
  } else {
    try {
      attribute = header["Destination Address"].toArray();
    } catch (const HeaderAttributeNotFoundException &hanfe) {
      qDebug() << hanfe.errorMessage() << " in HeaderUtil::getTCPFlag";
      return "";
    }
  }
  // Creating the IP Address
  IPAddress address(attribute);
  return address.toString();
}

QString HeaderUtil::getIPFlags(const Package &data) {
  // Getting the IP Header
  Header header;
  try {
    header = data[HeaderType::IP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getIPAddress";
    return "";
  }
  QVector<quint8> attribute;
  // Getting the flags
  try {
    attribute = header["Flags"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getIPFlag";
    return "";
  }

  return QString("0x") + QString::number(attribute[0], 16);
}

QString HeaderUtil::getIPFlag(const Package &data, const IPFlag &flagName) {
  // Getting the IP Header
  Header header;
  try {
    header = data[HeaderType::IP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getIPAddress";
    return "";
  }
  QVector<quint8> attribute;
  // Getting the flags
  try {
    attribute = header["Flags"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getIPFlag";
    return "";
  }

  quint8 flags = attribute[0];
  QString returnString;

  // Checking which flag
  if (flagName == IPFlag::DF) {
    ((flags >> 1) & 1) != 0 ? returnString = "Set" : returnString = "Not Set";
    return returnString;
  }
  if (flagName == IPFlag::MF) {
    ((flags >> 2) & 1) != 0 ? returnString = "Set" : returnString = "Not Set";
    return returnString;
  }
  qDebug() << "This flag does not exist: " << flagName
           << " in HeaderUtil::getIPFlag";

  return "";
}

QString HeaderUtil::getIPNextProtocol(const Package &data) {
  // Getting the IP Header
  Header header;
  try {
    header = data[HeaderType::IP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getIPAddress";
    return "";
  }
  QVector<quint8> attribute;
  // Getting the next Protocol
  try {
    attribute = header["Protocol"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getIPNextProtocol";
    return "";
  }

  // Returning the right String
  if (attribute[0] == 17) {
    return "UDP";
  }
  if (attribute[0] == 6) {
    return "TCP";
  }
  if (attribute[0] == 0) {
    return "";
  }
  qDebug()
      << "Cannot find a following Protocol in HeaderUtil::getIPNextProtocol";
  return "";
}

QString HeaderUtil::getIPHeaderLength(const Package &data) {
  Header header;
  try {
    header = data[HeaderType::IP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getIPAddress";
    return "";
  }

  QVector<quint8> attribute;
  // Getting the next Protocol
  try {
    attribute = header["Header Length"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getIPNextProtocol";
    return "";
  }

  return QString::number(attribute[0] * 4) + " Bytes";
}

QString HeaderUtil::getIPTOS(const Package &data) {
  Header header;
  try {
    header = data[HeaderType::IP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getIPAddress";
    return "";
  }

  QVector<quint8> attribute;
  // Getting the next Protocol
  try {
    attribute = header["Type Of Service"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getIPNextProtocol";
    return "";
  }

  return QString("0x") +
         QString::number(attribute[0], 16).rightJustified(2, '0');
}

QString HeaderUtil::getIPTotalLength(const Package &data) {
  Header header;
  try {
    header = data[HeaderType::IP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getIPAddress";
    return "";
  }

  QVector<quint8> attribute;
  // Getting the next Protocol
  try {
    attribute = header["Total Length"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getIPNextProtocol";
    return "";
  }

  quint16 length = attribute[0] << 8 | attribute[1];

  return QString::number(length);
}

QString HeaderUtil::getIPIdentification(const Package &data) {
  Header header;
  try {
    header = data[HeaderType::IP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getIPAddress";
    return "";
  }

  QVector<quint8> attribute;
  // Getting the next Protocol
  try {
    attribute = header["Identification"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getIPNextProtocol";
    return "";
  }

  quint16 id = attribute[0] << 8 | attribute[1];

  return QString("0x") + QString::number(id, 16).rightJustified(4, '0');
}

QString HeaderUtil::getIPTTL(const Package &data) {
  Header header;
  try {
    header = data[HeaderType::IP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getIPAddress";
    return "";
  }

  QVector<quint8> attribute;
  // Getting the next Protocol
  try {
    attribute = header["Time To Live"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getIPNextProtocol";
    return "";
  }

  return QString::number(attribute[0]);
}

QString HeaderUtil::getIPChecksum(const Package &data) {
  Header header;
  try {
    header = data[HeaderType::IP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getIPAddress";
    return "";
  }

  QVector<quint8> attribute;
  // Getting the next Protocol
  try {
    attribute = header["Checksum"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getIPNextProtocol";
    return "";
  }

  quint16 checksum = attribute[0] << 8 | attribute[1];

  return QString("0x") + QString::number(checksum, 16).toUpper();
}

QString HeaderUtil::getIPFragmentOffset(const Package &data) {
  Header header;
  try {
    header = data[HeaderType::IP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getIPAddress";
    return "";
  }

  QVector<quint8> attribute;
  // Getting the next Protocol
  try {
    attribute = header["Fragment Offset"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getIPNextProtocol";
    return "";
  }

  quint16 offset = attribute[0] << 8 | attribute[1];

  return QString::number(offset);
}

// TCP

QString HeaderUtil::getPort(const Package &data, bool src) {
  // Getting the right header
  Header header;
  try {
    header = data[HeaderType::TCP];
  } catch (const HeaderNotFoundException &hnfe) {
    try {
      header = data[HeaderType::UDP];
    } catch (const HeaderNotFoundException &hnfe) {
      qDebug() << hnfe.errorMessage() << " in HeaderUtil::getPort";
      return "";
    }
  }

  // Getting the source or destination port
  QVector<quint8> attribute;
  if (src) {
    try {
      attribute = header["Source Port"].toArray();
    } catch (const HeaderAttributeNotFoundException &hanfe) {
      qDebug() << hanfe.errorMessage() << " in HeaderUtil::getPort";
      return "";
    }
  } else {
    try {
      attribute = header["Destination Port"].toArray();
    } catch (const HeaderAttributeNotFoundException &hanfe) {
      qDebug() << hanfe.errorMessage() << " in HeaderUtil::getPort";
      return "";
    }
  }

  quint16 port = attribute[0] << 8 | attribute[1];

  return QString::number(port);
}

QString HeaderUtil::getTCPFlags(const Package &data) {
  // Get header
  Header header;
  try {
    header = data[HeaderType::TCP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getTCPFlag";
    return "";
  }

  // Get flags
  QVector<quint8> attribute;
  try {
    attribute = header["Flags"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getTCPFlag";
    return "";
  }

  return QString("0x") +
         QString::number(attribute[0], 16).rightJustified(3, '0');
}

QString HeaderUtil::getTCPFlag(const Package &data, const TCPFlag &flagName) {
  // Get header
  Header header;
  try {
    header = data[HeaderType::TCP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getTCPFlag";
    return "";
  }

  // Get flags
  QVector<quint8> attribute;
  try {
    attribute = header["Flags"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getTCPFlag";
    return "";
  }

  // putting the flags from quint8* together to quint16
  quint16 flag = attribute[0] << 8 | attribute[1];
  QString returnString;

  // checking ack flag
  switch (flagName) {
  case TCPFlag::NS:
    returnString = (flag & 0b1000'0000) ? "Set" : "Not Set";
    break;
  case TCPFlag::CWR:
    returnString = (flag & 0b1000'0000) ? "Set" : "Not Set";
    break;
  case TCPFlag::ECE:
    returnString = (flag & 0b100'0000) ? "Set" : "Not Set";
    break;
  case TCPFlag::URG:
    returnString = (flag & 0b10'0000) ? "Set" : "Not Set";
    break;
  case TCPFlag::ACK:
    returnString = (flag & 0b1'0000) ? "Set" : "Not Set";
    break;
  case TCPFlag::PSH:
    returnString = (flag & 0b1000) ? "Set" : "Not Set";
    break;
  case TCPFlag::RST:
    returnString = (flag & 0b100) ? "Set" : "Not Set";
    break;
  case TCPFlag::SYN:
    returnString = (flag & 0b10) ? "Set" : "Not Set";
    break;
  case TCPFlag::FIN:
    returnString = (flag & 0b1) ? "Set" : "Not Set";
    break;
  default:
    qDebug() << "Unknown flag name in HeaderUtil::getTCPFlag";
    break;
  }
  return returnString;
}

QString HeaderUtil::getTCPSequenceNumber(const Package &data) {
  // Get header
  Header header;
  try {
    header = data[HeaderType::TCP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getTCPFlag";
    return "";
  }

  // Get attribute
  QVector<quint8> attribute;
  try {
    attribute = header["Sequence Number"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getTCPFlag";
    return "";
  }

  quint32 sequenceNumber = attribute[0] << 24 | attribute[1] << 16 |
                           attribute[2] << 8 | attribute[3];
  return QString::number(sequenceNumber);
}

QString HeaderUtil::getTCPAcknowledgementNumber(const Package &data) {
  // Get header
  Header header;
  try {
    header = data[HeaderType::TCP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getTCPFlag";
    return "";
  }

  // Get attribute
  QVector<quint8> attribute;
  try {
    attribute = header["Acknowledgment Number"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getTCPFlag";
    return "";
  }

  quint32 sequenceNumber = attribute[0] << 24 | attribute[1] << 16 |
                           attribute[2] << 8 | attribute[3];
  return QString::number(sequenceNumber);
}

QString HeaderUtil::getTCPHeaderLength(const Package &data) {
  // Get header
  Header header;
  try {
    header = data[HeaderType::TCP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getTCPFlag";
    return "";
  }

  // Get attribute
  QVector<quint8> attribute;
  try {
    attribute = header["Header Length"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getTCPFlag";
    return "";
  }

  return QString::number(attribute[0] * 4) + " Bytes";
}

QString HeaderUtil::getTCPWindow(const Package &data) {
  // Get header
  Header header;
  try {
    header = data[HeaderType::TCP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getTCPFlag";
    return "";
  }

  // Get attribute
  QVector<quint8> attribute;
  try {
    attribute = header["Window"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getTCPFlag";
    return "";
  }

  quint16 sequenceNumber = attribute[0] << 8 | attribute[1];
  return QString::number(sequenceNumber);
}

QString HeaderUtil::getTCPChecksum(const Package &data) {
  Header header;
  try {
    header = data[HeaderType::TCP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getTCPChecksum";
    return "";
  }

  // Get attribute
  QVector<quint8> attribute;
  try {
    attribute = header["Checksum"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getTCPChecksum";
    return "";
  }

  quint16 checksum = attribute[0] << 8 | attribute[1];
  return QString("0x") +
         QString::number(checksum, 16).toUpper().rightJustified(4, '0');
}

QString HeaderUtil::getTCPUrgentPointer(const Package &data) {
  Header header;
  try {
    header = data[HeaderType::TCP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getTCPUrgentPointer";
    return "";
  }

  // Get attribute
  QVector<quint8> attribute;
  try {
    attribute = header["Urgent Pointer"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getTCPUrgentPointer";
    return "";
  }

  quint16 urgentPointer = attribute[0] << 8 | attribute[1];
  return QString::number(urgentPointer);
}

// UDP

QString HeaderUtil::getUDPChecksum(const Package &data) {
  Header header;
  try {
    header = data[HeaderType::UDP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getUDPChecksum";
    return "";
  }

  QVector<quint8> attribute;
  try {
    attribute = header["Checksum"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getUDPChecksum";
    return "";
  }

  quint16 checksum = attribute[0] << 8 | attribute[1];

  return QString("0x") +
         QString::number(checksum, 16).toUpper().rightJustified(4, '0');
}

QString HeaderUtil::getUDPLength(const Package &data) {
  Header header;
  try {
    header = data[HeaderType::UDP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getUDPLength";
    return "";
  }

  QVector<quint8> attribute;
  try {
    attribute = header["Length"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getUDPLength";
    return "";
  }

  quint16 length = attribute[0] << 8 | attribute[1];

  return QString::number(length);
}

// HTTP

QString HeaderUtil::getHTTPAttribute(const Package &data,
                                     const QString &attributeName) {
  // Getting the Header
  Header header;
  try {
    header = data[HeaderType::HTTP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::ggetAttributeAsString";
    return "";
  }

  // Getting the attribute
  QVector<quint8> attribute;
  try {
    attribute = header[attributeName].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getAttributeAsString";
    return "";
  }

  // Converting to String
  QString returnString;
  for (unsigned int i = 0; i < attribute.size(); i++) {
    returnString.append(static_cast<char>(attribute[i]));
  }
  return returnString;
}

bool HeaderUtil::getHTTPIsResponse(const Package &data) {
  // Getting the Header
  Header header;
  try {
    header = data[HeaderType::HTTP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::ggetAttributeAsString";
    return false;
  }

  return header.headerList().size() == 4;
}

bool HeaderUtil::getHTTPIsRequest(const Package &data) {
  // Getting the Header
  Header header;
  try {
    header = data[HeaderType::HTTP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::ggetAttributeAsString";
    return false;
  }

  return header.headerList().size() == 3;
}

// DNS

QString HeaderUtil::getDNSID(const Package &data) {
  Header header;
  try {
    header = data[HeaderType::DNS];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getDNSID";
    return "";
  }

  QVector<quint8> attribute;
  try {
    attribute = header["Transaction ID"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getDNSID";
    return "";
  }

  quint16 dnsID = attribute[0] << 8 | attribute[1];

  return QString("0x") +
         QString::number(dnsID, 16).toUpper().rightJustified(4, '0');
}

QString HeaderUtil::getDNSFlags(const Package &data) {
  Header header;
  try {
    header = data[HeaderType::DNS];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getDNSFlag";
    return "";
  }

  QVector<quint8> attribute;
  try {
    attribute = header["Flags"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getDNSFlag";
    return "";
  }

  quint16 dnsFlag = attribute[0] << 8 | attribute[1];

  return QString("0x") + QString::number(dnsFlag, 16).rightJustified(4, '0');
}

QString HeaderUtil::getDNSFlag(const Package &data, const DNSFlag &flagName) {
  Header header;
  try {
    header = data[HeaderType::DNS];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getDNSFlag";
    return "";
  }

  QVector<quint8> attribute;
  try {
    attribute = header["Flags"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getDNSFlag";
    return "";
  }

  quint16 dnsFlag = attribute[0] << 8 | attribute[1];

  switch (flagName) {
  case DNSFlag::RESPONSE:
    return dnsFlag & 0b1000'0000'0000'0000 ? "Message is a response"
                                           : "Message is a query";
  case DNSFlag::OPCODE: {
    switch (dnsFlag & 0b111'1000'0000'0000 >> 11) {
    case 0:
      return "Standard query (0)";
    case 1:
      return "Inverse query (1)";
    case 2:
      return "Server status request (2)";
    case 3:
      return "Reserved for future use (3)";
    case 4:
      return "Notify (4)";
    case 5:
      return "Update (5)";
    case 6:
      return "DNS Stateful Operations (DSO) (6)";
    default:
      return "Unknown opcode (" +
             QString::number(dnsFlag & 0b111'1000'0000'0000 >> 11) + ")";
    }
  }
  case DNSFlag::AUTHORITATIVE:
    return dnsFlag & 0b0000'0100'0000'0000
               ? "Server is an authority for domain"
               : "Server is not an authority for domain";
  case DNSFlag::TRUNCATED:
    return dnsFlag & 0b0000'0010'0000'0000 ? "Message is truncated"
                                           : "Message is not truncated";
  case DNSFlag::RECURSION_DESIRED:
    return dnsFlag & 0b0000'0001'0000'0000 ? "Do query recursively"
                                           : "Do not query recursively";
  case DNSFlag::RECURSION_AVAILABLE:
    return dnsFlag & 0b0000'0000'1000'0000
               ? "Server can do recursive queries"
               : "Server cannot do recursive queries";
  case DNSFlag::ANSWER_AUTHENTICATED:
    return dnsFlag & 0b0000'0000'0100'0000
               ? "Answer/authority portion was authenticated by server"
               : "Answer/authority portion was not authenticated by server";
  case DNSFlag::NON_AUTHENTICATED_DATA:
    return dnsFlag & 0b0000'0000'0010'0000 ? "Acceptable" : "Unacceptable";
  case DNSFlag::REPLY_CODE: {
    switch (dnsFlag & 0b1111) {
    case 0:
      return "No error (0)";
    case 1:
      return "Format error (1)";
    case 2:
      return "Server failure (2)";
    case 3:
      return "Non-existent domain (3)";
    case 4:
      return "Query type not implemented (4)";
    default:
      return "Unknown error (" + QString::number(dnsFlag & 0b1111) + ")";
    }
  }
  default:
    return QString();
  }
}

QString HeaderUtil::getDNSQuestions(const Package &data) {
  Header header;
  try {
    header = data[HeaderType::DNS];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getDNSQuestions";
    return "";
  }

  QVector<quint8> attribute;
  quint16 dnsQuestions = 0;
  try {
    attribute = header["Questions"].toArray();
    dnsQuestions = attribute[0] << 8 | attribute[1];
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getDNSQuestions";
    return "";
  }

  return QString::number(dnsQuestions);
}

QString HeaderUtil::getDNSAnswerRRs(const Package &data) {
  Header header;
  try {
    header = data[HeaderType::DNS];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getDNSQuestions";
    return "";
  }

  QVector<quint8> attribute;
  try {
    attribute = header["Answer RRs"].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getDNSQuestions";
    return "";
  }

  quint16 dnsAnswers = attribute[0] << 8 | attribute[1];

  return QString::number(dnsAnswers);
}

QString HeaderUtil::getDNSQuery(const Package &data, int index,
                                const RRAttribute &attr) {
  Header header;
  try {
    header = data[HeaderType::DNS];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getDNSQuestions";
    return "";
  }

  QVector<quint8> attribute;
  try {
    attribute = header["Query " + QString::number(index)].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getDNSQuestions";
    return "";
  }

  QString name = "";
  QString type = "";
  QString _class = "";

  unsigned int i = 0;

  while (attribute[i] != 0x00) {
    name.append(static_cast<char>(attribute[i++]));
  }
  i++;
  quint16 typeValue = attribute[i++] << 8;
  switch (typeValue | attribute[i++]) {
  case 0x0001:
    type = "A";
    break;
  case 0x0002:
    type = "NS";
    break;
  case 0x0005:
    type = "CNAME";
    break;
  case 0x0006:
    type = "SOA";
    break;
  case 0x000c:
    type = "PTR";
    break;
  case 0x000f:
    type = "MX";
    break;
  case 0x0010:
    type = "TXT";
    break;
  case 0x001c:
    type = "AAAA";
    break;
  default:
    type = "Unknown";
    break;
  }
  quint16 classNumber = attribute[i++] << 8;
  _class = (classNumber | attribute[i]) == 0x0001 ? "IN" : "Unknown";

  switch (attr) {
  case RRAttribute::FULL_DATA:
    return name + ": type " + type + ", class " + _class;
  case RRAttribute::NAME:
    return name;
  case RRAttribute::TYPE:
    return type;
  case RRAttribute::CLASS:
    return _class;
  default:
    return "";
  }
}

QString HeaderUtil::getDNSAnswer(const Package &data, int index,
                                 const RRAttribute &attr) {
  Header header;
  try {
    header = data[HeaderType::DNS];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getDNSQuestions";
    return "";
  }

  QVector<quint8> attribute;
  try {
    attribute = header["Answer " + QString::number(index)].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getDNSQuestions";
    return "";
  }

  QString name = "";
  QString type = "";
  QString _class = "";
  QString ttl = "";
  QString dataLength = "";

  unsigned int i = 0;

  while (attribute[i] != 0x00) {
    name.append(static_cast<char>(attribute[i++]));
  }
  i++;

  quint16 typeValue = attribute[i++] << 8;
  switch (typeValue | attribute[i++]) {
  case 0x0001:
    type = "A";
    break;
  case 0x0002:
    type = "NS";
    break;
  case 0x0005:
    type = "CNAME";
    break;
  case 0x0006:
    type = "SOA";
    break;
  case 0x000c:
    type = "PTR";
    break;
  case 0x000f:
    type = "MX";
    break;
  case 0x0010:
    type = "TXT";
    break;
  case 0x001c:
    type = "AAAA";
    break;
  default:
    type = "Unknown";
    break;
  }

  quint16 classNumber = attribute[i++] << 8;
  _class = (classNumber | attribute[i++]) == 0x0001 ? "IN" : "Unknown";

  quint32 ttlValue = attribute[i++] << 24;
  ttlValue |= attribute[i++] << 16;
  ttlValue |= attribute[i++] << 8;
  ttlValue |= attribute[i++];
  ttl = QString::number(ttlValue);

  quint16 dataLengthValue = attribute[i++] << 8;
  dataLengthValue |= attribute[i++];
  dataLength = QString::number(dataLengthValue);

  QVector<quint8> ipData;
  ipData.append(attribute[i++]);
  ipData.append(attribute[i++]);
  ipData.append(attribute[i++]);
  ipData.append(attribute[i]);
  IPAddress ip(ipData);

  switch (attr) {
  case RRAttribute::FULL_DATA:
    return name + ": type " + type + ", class " + _class + ", addr " +
           ip.toString();
  case RRAttribute::NAME:
    return name;
  case RRAttribute::TYPE:
    return type;
  case RRAttribute::CLASS:
    return _class;
  case RRAttribute::TTL:
    return ttl;
  case RRAttribute::DATA_LENGTH:
    return dataLength;
  case RRAttribute::DATA:
    return ip.toString();
  default:
    return "";
  }
}

IPAddress HeaderUtil::getDNSAnswerIPAddress(const Package &data, int index) {
  Header header;
  try {
    header = data[HeaderType::DNS];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage() << " in HeaderUtil::getDNSAnswerIPAddress";
    return IPAddress();
  }

  QVector<quint8> attribute;
  try {
    attribute = header["Answer " + QString::number(index)].toArray();
  } catch (const HeaderAttributeNotFoundException &hanfe) {
    qDebug() << hanfe.errorMessage() << " in HeaderUtil::getDNSAnswerIPAddress";
    return IPAddress();
  }

  unsigned int i = 0;

  while (attribute[i] != 0x00) {
    i++;
  }
  i += 11;

  QVector<quint8> ipData;
  ipData.append(attribute[i++]);
  ipData.append(attribute[i++]);
  ipData.append(attribute[i++]);
  ipData.append(attribute[i]);

  return IPAddress(ipData);
}

// Allrounder

QString HeaderUtil::getPackageLength(const Package &package) {
  return QString::number(package.size());
}

HeaderType HeaderUtil::getTopProtocol(const Package &data) {
  return data.headers().constFirst().type();
}

IPAddress HeaderUtil::getIPAddressAsIPAddress(const Package &data, bool src) {
  // Getting the IP Header
  Header header;
  try {
    header = data[HeaderType::IP];
  } catch (const HeaderNotFoundException &hnfe) {
    qDebug() << hnfe.errorMessage()
             << " in HeaderUtil::getIPAddressAsIPAddress";
    return IPAddress();
  }

  QVector<quint8> attribute;
  // Getting the source or destination address
  if (src) {
    try {
      attribute = header["Source Address"].toArray();
    } catch (const HeaderAttributeNotFoundException &hanfe) {
      qDebug() << hanfe.errorMessage()
               << " in HeaderUtil::getIPAddressAsIPAddress";
      return IPAddress();
    }
  } else {
    try {
      attribute = header["Destination Address"].toArray();
    } catch (const HeaderAttributeNotFoundException &hanfe) {
      qDebug() << hanfe.errorMessage()
               << " in HeaderUtil::getIPAddressAsIPAddress";
      return IPAddress();
    }
  }

  return IPAddress(attribute);
}

Port HeaderUtil::getPortAsPort(const Package &data, bool src) {
  // Getting the right header
  Header header;
  try {
    header = data[HeaderType::TCP];
  } catch (const HeaderNotFoundException &hnfe) {
    try {
      header = data[HeaderType::UDP];
    } catch (const HeaderNotFoundException &hnfe) {
      qDebug() << hnfe.errorMessage() << " in HeaderUtil::getPortAsPort";
      return Port();
    }
  }

  // Getting the source or destination port
  QVector<quint8> attribute;
  if (src) {
    try {
      attribute = header["Source Port"].toArray();
    } catch (const HeaderAttributeNotFoundException &hanfe) {
      qDebug() << hanfe.errorMessage() << " in HeaderUtil::getPortAsPort";
      return Port();
    }
  } else {
    try {
      attribute = header["Destination Port"].toArray();
    } catch (const HeaderAttributeNotFoundException &hanfe) {
      qDebug() << hanfe.errorMessage() << " in HeaderUtil::getPortAsPort";
      return Port();
    }
  }

  quint16 port = attribute[0] << 8 | attribute[1];

  return Port(port);
}
