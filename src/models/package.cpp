#include "package.h"
#include "src/protocols/Headernotfoundexception.h"

using namespace NetSim;

Package::Package(const QString &info)
    : m_headers(), m_info(info), m_content() {}

Package::Package(const QString &info, const QString &content)
    : m_headers(), m_info(info), m_content(content) {}

QString Package::content() const { return m_content; }

QList<Header> Package::headers() const { return m_headers; }

void Package::addHeader(const Header &header) { m_headers.append(header); }

QString Package::info() const { return m_info; }

void Package::setContent(const QString &content) { this->m_content = content; }

quint16 Package::size() const {
  quint16 length = content().length();
  for (const Header &header : m_headers) {
    length += header.size();
  }
  return length;
}

void Package::changePortAndIP(const Port &number, const IPAddress &address,
                              bool src) {
  if (src) {
    HeaderAttribute srcPort("Source Port", 16, number.portNumber());
    try {
      (*this)[HeaderType::TCP]["Source Port"].setContent(srcPort.toArray());
      qInfo() << "Successfully changed the TCP Source Port to: "
              << QString::number(number.portNumber());
    } catch (const HeaderNotFoundException &e) {
      try {
        (*this)[HeaderType::UDP]["Source Port"].setContent(srcPort.toArray());
        qInfo() << "Successfully changed the UDP Source Port to: "
                << QString::number(number.portNumber());
      } catch (const HeaderNotFoundException &e) {
        qDebug() << e.errorMessage()
                 << " Package is neither a TCP nor a UDP Package. Could not "
                    "change the Source Port.";
      }
    }
  } else {
    HeaderAttribute destPort("Destination Port", 16, number.portNumber());
    try {
      (*this)[HeaderType::TCP]["Destination Port"].setContent(
          destPort.toArray());
      qInfo() << "Successfully changed the TCP Destination Port to: "
              << QString::number(number.portNumber());
    } catch (const HeaderNotFoundException &e) {
      try {
        (*this)[HeaderType::UDP]["Destination Port"].setContent(
            destPort.toArray());
        qInfo() << "Successfully changed the UDP Destination Port to: "
                << QString::number(number.portNumber());
      } catch (const HeaderNotFoundException &e) {
        qDebug() << e.errorMessage()
                 << " Package is neither a TCP nor a UDP Package. Could not "
                    "change the Destination Port.";
      }
    }
  }

  if (src) {
    try {
      (*this)[HeaderType::IP]["Source Address"].setContent(address.toArray());
      qInfo() << "Successfully changed the Source IP Address to: "
              << address.toString();
    } catch (const HeaderNotFoundException &e) {
      qDebug() << e.errorMessage()
               << " Package is not an IP Package. Could not change the Source "
                  "Address.";
    }

  } else {
    try {
      (*this)[HeaderType::IP]["Destination Address"].setContent(
          address.toArray());
      qInfo() << "Successfully changed the Destination IP Address to: "
              << address.toString();
    } catch (const HeaderNotFoundException &e) {
      qDebug() << e.errorMessage()
               << " Package is not an IP Package. Could not change the "
                  "Destination Address.";
    }
  }
}

void Package::changeEthernetHeader(const MACAddress &srcAddress,
                                   const MACAddress &destAddress) {
  try {
    (*this)[HeaderType::MAC]["Destination MAC Address"].setContent(
        destAddress.toArray());
    qInfo() << "Successfully changed the Destination MAC Address to: "
            << destAddress.toString();
  } catch (const HeaderNotFoundException &e) {
    qDebug() << e.errorMessage()
             << " Package is not a MAC Package. Could not change the "
                "Destination MAC Address.";
  }

  try {
    (*this)[HeaderType::MAC]["Source MAC Address"].setContent(
        srcAddress.toArray());
    qInfo() << "Successfully changed the Source MAC Address to: "
            << srcAddress.toString();
  } catch (const HeaderNotFoundException &e) {
    qDebug() << e.errorMessage()
             << " Package is not a MAC Package. Could not change the Source "
                "MAC Address.";
  }
}

Header &Package::operator[](const HeaderType &type) {
  for (int i = 0; i < m_headers.size(); i++) {
    if (type == m_headers[i].type()) {
      return m_headers[i];
    }
  }
  throw HeaderNotFoundException("Could not find Header with type " +
                                QString::number(type));
}

Header Package::operator[](const HeaderType &type) const {
  for (int i = 0; i < m_headers.size(); i++) {
    if (type == m_headers[i].type()) {
      return m_headers[i];
    }
  }
  throw HeaderNotFoundException("Could not find Header with type " +
                                QString::number(type));
}
