#include "packagedatabase.h"
#include "src/protocols/http.h"
#include "src/protocols/tcp.h"
#include "src/protocols/ipv4.h"
#include "src/protocols/mac.h"

PackageDatabase::PackageDatabase()
{
    Package package("Test Package", "There is no content");
    HTTP::initHTTPRequest("GET", "beispiel.de", "HTTP/1.1", package);
    IPAddress src = IPAddress::getRandomAddress(false);
    IPAddress dst = IPAddress::getRandomAddress(false);
    TCP::initHeader(src, dst, Port(80), Port(80), 28, 394, false, false, false, false, 200, package, 19);
    IPv4::initHeader(69, false, false, 0, 10, 6, src, dst, package);
    MAC::initHeader(package, MACAddress::getRandomAddress(), MACAddress::getRandomAddress(), 1000);
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
