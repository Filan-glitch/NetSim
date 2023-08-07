#include "packagedatabase.h"
#include "src/protocols/http.h"
#include "src/protocols/tcp.h"
#include "src/protocols/ipv4.h"
#include "src/protocols/mac.h"
#include "src/protocols/dns.h"
#include "src/protocols/udp.h"

PackageDatabase::PackageDatabase()
{
    Package package("HTTP Test Request");
    HTTP::initHTTPRequest("GET", "/test/index.html", "HTTP/1.1", package);
    IPAddress src = IPAddress::getRandomAddress(false);
    IPAddress dst = IPAddress::getRandomAddress(false);
    TCP::initHeader(src, dst, Port(1024), Port(80), 1, 1, true, false, false, false, 200, package);
    IPv4::initHeader(25650, false, false, 0, 10, 6, src, dst, package);
    MAC::initHeader(package, MACAddress::getRandomAddress(), MACAddress::getRandomAddress(), 2048);

    Package package2("DNS Test Response");
    QList<DNSEntry> queryList;
    queryList.append(DNSEntry("beispiel.de", 1, 1));
    QList<DNSEntry> answerList;
    QVector<quint8> ip;
    ip.append(127);
    ip.append(22);
    ip.append(99);
    ip.append(2);
    answerList.append(DNSEntry("beispiel.de", 1, 1, 21600, 4, ip));
    DNS::initDNSResponse(package2, queryList, answerList);
    UDP::initHeader(Port(2048), Port(53), package2);
    IPAddress src2 = IPAddress::getRandomAddress(false);
    IPAddress dst2 = IPAddress::getRandomAddress(false);
    IPv4::initHeader(83, false, false, 0, 10, 17, src2, dst2, package2);
    MAC::initHeader(package2, MACAddress::getRandomAddress(), MACAddress::getRandomAddress(), 2048);

    Package package3("HTTP Test Package");
    HTTP::initHTTPResponse("HTTP/1.1", 200, "OK", package3, "<html>Congratulations. You've downloaded the file test.html!</html>");
    TCP::initHeader(dst, src, Port(80), Port(1024), 1, 200, false, false, false, false, 200, package3);
    IPv4::initHeader(25231, false, false, 0, 10, 6, dst, src, package3);
    MAC::initHeader(package3, MACAddress::getRandomAddress(), MACAddress::getRandomAddress(), 2048);

    m_packageList.append(package2);
    m_packageList.append(package);
    m_packageList.append(package3);
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
