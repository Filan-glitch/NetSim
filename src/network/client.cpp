#include "client.h"
#include "src/protocols/headerutil.h"
#include "src/protocols/tcp.h"
#include "src/network/router.h"


Client::Client(const NetworkCard &networkCard) : Host(networkCard)
{
}

void Client::execDomainResolution(const QString &domain){
    if(getDomainTable().contains(domain)) {
        return;
    }

    //DNS Process
    Process dnsProcess = getProcessByName("DNS");

    //DNS Package
    Package dnsRequest = dnsProcess.getDNSRequest(domain);

    MACAddress routerMAC = this->getHostTable().value(this->getDomainTable().value(QString("dns.beispiel.de")));
    Router* router = this->getRouterByMACAddress(routerMAC);
    router->receivePackage(dnsRequest);
}

void Client::execHandShake(const IPAddress &address){
    MACAddress routerMAC = this->getHostTable().value(address);
    Router* router = this->getRouterByMACAddress(routerMAC);

    if(router == nullptr){
        qDebug() << "Router is nullptr in Client::execHandShake";
        return;
    }

    Process httpProcess = getProcessByName("HTTP");
    router->receivePackage(httpProcess.getHandShakePackage(address,true,true));
}

void Client::execHTTPRequest(const IPAddress &address, const QString &uri){
    MACAddress routerMAC = this->getHostTable().value(address);
    Router* router = this->getRouterByMACAddress(routerMAC);

    if(router == nullptr){
        qDebug() << "Router is nullptr in Client::execHTTPRequest";
        return;
    }

    Process httpProcess = getProcessByName("HTTP");

    router->receivePackage(httpProcess.getHTTPRequest(uri,address));
}

void Client::execCloseConnection(const IPAddress &address){
    MACAddress routerMAC = this->getHostTable().value(address);
    Router* router = this->getRouterByMACAddress(routerMAC);

    if(router == nullptr){
        qDebug() << "Router is nullptr in Client::execHandShake";
        return;
    }

    Process httpProcess = getProcessByName("HTTP");

    router->receivePackage(httpProcess.getCloseConnectionPackage(address,true,true));
}

void Client::receivePackage(Package data){
    //TODO Add to Packagelist
    getPackages()->addPackage(data);

    //Receives a DNS Response Package from Server
    if(HeaderUtil::getApplicationProtocol(data) == HeaderType::DNS) {
        for(auto i = 0; i < HeaderUtil::getDNSAnswerRRs(data).toInt(); i++) {
            addDomain(HeaderUtil::getDNSAnswer(data, i, RRAttribute::NAME), HeaderUtil::getDNSAnswerIPAddress(data, i));
        }
        return;
    }

    //Receives a TCP Handshake Package from Server
    if(HeaderUtil::getTCPFlag(data, TCPFlag::SYN) == "Set" && HeaderUtil::getTCPFlag(data, TCPFlag::ACK) == "Set"){
        MACAddress routerMAC = this->getHostTable().value(HeaderUtil::getIPAddressAsIPAddress(data, true));
        Router* router = this->getRouterByMACAddress(routerMAC);

        if(router == nullptr){
            qDebug() << "Router is nullptr in Client::receivePackage";
            return;
        }

        Process httpProcess = getProcessByName("HTTP");

        router->receivePackage(httpProcess.getHandShakePackage(HeaderUtil::getIPAddressAsIPAddress(data,true),false,true));
    }

    //Receives a Closing Package from Server
    if(HeaderUtil::getTCPFlag(data, TCPFlag::FIN) == "Set" && HeaderUtil::getTCPFlag(data, TCPFlag::ACK) == "Set"){
        MACAddress routerMAC = this->getHostTable().value(HeaderUtil::getIPAddressAsIPAddress(data, true));
        Router* router = this->getRouterByMACAddress(routerMAC);

        if(router == nullptr){
            qDebug() << "Router is nullptr in Client::receivePackage";
            return;
        }

        Process httpProcess = getProcessByName("HTTP");

        router->receivePackage(httpProcess.getCloseConnectionPackage(HeaderUtil::getIPAddressAsIPAddress(data,true),false,true));
    }
}
