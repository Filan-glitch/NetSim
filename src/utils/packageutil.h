#ifndef PACKAGEUTIL_H
#define PACKAGEUTIL_H

#include "src/models/ipv4address.h"
#include "src/models/package.h"
#include "src/models/port.h"
#include <QString>

namespace NetSim {

enum Protocol {
    DNS,
    HTTP,
    DHCP,
    TCP,
    UDP,
    ICMP,
    ARP,
    IPv4,
    IPv6,
    ETHERNET2,
    UNKNOWN
};

class PackageUtil
{
public:
    static QString getIPAddress(const Package &package, bool source);
    static Protocol getTopProtocol(const Package &package);
    static IPv4Address getIPAddressAsIPAddress(Package, bool);
    static Port getPortAsPort(Package, bool);
};
} // namespace NetSim

#endif // PACKAGEUTIL_H
