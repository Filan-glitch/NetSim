#ifndef PACKAGE_H
#define PACKAGE_H

#include "ipaddress.h"
#include "macaddress.h"
#include "port.h"
#include "src/protocols/header.h"
#include <QList>

namespace NetSim {
class Package;
}

class Package {
public:
  Package();

  Package(const QString &info);

  Package(const QString &info, const QString &content);

  QString content() const;

  QList<Header> headers() const;

  QString info() const;

  quint16 size() const;

  void addHeader(const Header &header);

  void setContent(const QString &content);

  void changePortAndIP(const Port &number, const IPAddress &address, bool src);

  void changeEthernetHeader(const MACAddress &srcAddress,
                            const MACAddress &destAddress);

  Header &operator[](const NetSim::HeaderType &type);

  Header operator[](const NetSim::HeaderType &type) const;

private:
  QList<Header> m_headers;

  QString m_info;

  QString m_content;

  void deleteHeaderByType(const NetSim::HeaderType &type);

  HeaderAttribute getHeaderAttributeByName(const Header &header,
                                           const QString &name) const;
};

#endif // PACKAGE_H
