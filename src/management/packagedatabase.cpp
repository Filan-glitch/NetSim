#include "packagedatabase.h"
#include "src/protocols/http.h"
#include "src/protocols/tcp.h"
#include "src/protocols/ipv4.h"
#include "src/protocols/mac.h"
#include "src/protocols/dns.h"
#include "src/protocols/udp.h"

PackageDatabase::PackageDatabase()
{
    Package package("HTTP Test Package", "There is no content");
    HTTP::initHTTPRequest("GET", "beispiel.de", "HTTP/1.1", package);
    IPAddress src = IPAddress::getRandomAddress(false);
    IPAddress dst = IPAddress::getRandomAddress(false);
    TCP::initHeader(src, dst, Port(1024), Port(80), 28, 394, false, false, false, false, 200, package);
    IPv4::initHeader(25650, false, false, 0, 10, 6, src, dst, package);
    MAC::initHeader(package, MACAddress::getRandomAddress(), MACAddress::getRandomAddress(), 2048);

    Package package2("DNS Test Package", "There is no content");
    QList<DNSEntry> list;
    list.append(DNSEntry("beispiel.de", 0x0001, 0x0001));
    DNS::initDNSRequest(package2, list);
    UDP::initHeader(Port(2048), Port(53), package2);
    IPAddress src2 = IPAddress::getRandomAddress(false);
    IPAddress dst2 = IPAddress::getRandomAddress(false);
    IPv4::initHeader(83, false, false, 0, 10, 17, src2, dst2, package2);
    MAC::initHeader(package2, MACAddress::getRandomAddress(), MACAddress::getRandomAddress(), 2048);
    m_packageList.append(package2);
    m_packageList.append(package);
}

QList<Package>* PackageDatabase::packageList()
{
    return &m_packageList;
}

PackageDatabase* PackageDatabase::instance()
{
    static PackageDatabase* model = new PackageDatabase();
    return model;
}
