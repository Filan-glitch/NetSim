#include "cablenotfoundexception.h"
#include "client.h"
#include "src/protocols/headerutil.h"
#include "src/protocols/tcp.h"
#include "src/network/router.h"


Client::Client(const NetworkCard &networkCard) : Host(networkCard)
{
}

void Client::execDomainResolution(const QString &domain){
    qInfo() << "Executing: Client::execDomainResolution" << " Client: " << this->getNetworkCard().getNetworkAddress().getAddressAsDecString();

    if(getDomainTable().contains(domain)) {
        qInfo() << "Client: " << this->getNetworkCard().getNetworkAddress().getAddressAsDecString() << " already has IPAddress to Domain: " << domain;
        return;
    }

    //DNS Process
    Process dnsProcess;
    try{
        dnsProcess = getProcessByName("DNS");
    }catch(std::runtime_error re){
        qDebug() << "Could not find Procces DNS ind Client::execDomainResolution";
        return;
    }

    //DNS Package
    Package dnsRequest = dnsProcess.getDNSRequest(domain);

    MACAddress routerMAC = this->getHostTable().value(this->getDomainTable().value(QString("dns.beispiel.de")));
    Router* router;
    try{
        router = this->getRouterByMACAddress(routerMAC);
    }catch(CableNotFoundException cnfe){
        qDebug() << cnfe.getErrorMessage() << " in Client::execDomainResolution";
        return;
    }

    qInfo() << "Client: " << this->getNetworkCard().getNetworkAddress().getAddressAsDecString() <<  " sends DNSRequest to Router: " << router->getNetworkCard().getPhysicalAddress().getAddressAsString();
    router->receivePackage(dnsRequest);
}

void Client::execHandShake(const IPAddress &address){
    qInfo() << "Executing: Client::execHandShake" << " Client: " << this->getNetworkCard().getNetworkAddress().getAddressAsDecString();

    MACAddress routerMAC = this->getHostTable().value(address);
    Router* router;
    try{
        router = this->getRouterByMACAddress(routerMAC);
    }catch(CableNotFoundException cnfe){
        qDebug() << cnfe.getErrorMessage() << " in Client::execHandShake";
        return;
    }


    if(router == nullptr){
        qDebug() << "Router is nullptr in Client::execHandShake";
        return;
    }

    Process httpProcess;
    try{
        httpProcess = getProcessByName("HTTP");
    }
    catch(std::runtime_error re){
        qDebug() << "Could not find Process HTTP in Client::execHandShake";
        return;
    }

    qInfo() << "Client: " << this->getNetworkCard().getNetworkAddress().getAddressAsDecString() << "sends TCP Handshake Package to Router: " << router->getNetworkCard().getPhysicalAddress().getAddressAsString();
    router->receivePackage(httpProcess.getHandShakePackage(address,true,true));
}

void Client::execHTTPRequest(const IPAddress &address, const QString &uri){
    qInfo() << "Executing: Client::execHTTPRequest" << " Client: " << this->getNetworkCard().getNetworkAddress().getAddressAsDecString();

    MACAddress routerMAC = this->getHostTable().value(address);
    Router* router;
    try{
        router = this->getRouterByMACAddress(routerMAC);
    }catch(CableNotFoundException cnfe){
        qDebug() << cnfe.getErrorMessage() << " in Client::execHTTPRequest";
        return;
    }

    if(router == nullptr){
        qDebug() << "Router is nullptr in Client::execHTTPRequest";
        return;
    }

    Process httpProcess;
    try{
        httpProcess = getProcessByName("HTTP");
    }catch(std::runtime_error re){
        qDebug() << "Could not find Process HTTP in Client::execHTTPRequest";
        return;
    }

    qInfo() << "Client: " << this->getNetworkCard().getNetworkAddress().getAddressAsDecString() <<" sends HTTPRequest Package to Router: " << router->getNetworkCard().getPhysicalAddress().getAddressAsString();
    router->receivePackage(httpProcess.getHTTPRequest(uri,address));
}

void Client::execCloseConnection(const IPAddress &address){
    qInfo() << "Executing: Client::execCloseConnection" << " Client: " << this->getNetworkCard().getNetworkAddress().getAddressAsDecString();

    MACAddress routerMAC = this->getHostTable().value(address);
    Router* router;
    try{
        router = this->getRouterByMACAddress(routerMAC);
    }catch(CableNotFoundException cnfe){
        qDebug() << cnfe.getErrorMessage() << " in Client::execCloseConnection";
        return;
    }

    if(router == nullptr){
        qDebug() << "Router is nullptr in Client::execHandShake";
        return;
    }

    Process httpProcess;
    try{
        httpProcess = getProcessByName("HTTP");
    }catch(std::runtime_error re){
        qDebug() << "Could not find Process HTTP in Client::execCloseConnection";
        return;
    }

    qInfo() << "Client sends close connection Package to router: " << router->getNetworkCard().getPhysicalAddress().getAddressAsString();
    router->receivePackage(httpProcess.getCloseConnectionPackage(address,true,true));
}

void Client::receivePackage(Package data){
    //Adds Package to packageDatabase
    getPackages()->addPackage(data);
    qInfo() << "Client: " << this->getNetworkCard().getNetworkAddress().getAddressAsDecString() << " received Package: " << data.getInfo() <<" Client: " << this->getNetworkCard().getNetworkAddress().getAddressAsDecString();

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
        Router* router;
        try{
            router = this->getRouterByMACAddress(routerMAC);
        }catch(CableNotFoundException cnfe){
            qDebug() << cnfe.getErrorMessage() << " in Client::receivePackage getting the TCP Handshake Package";
            return;
        }

        if(router == nullptr){
            qDebug() << "Router is nullptr in Client::receivePackage";
            return;
        }

        Process httpProcess;
        try{
            httpProcess = getProcessByName("HTTP");
        }catch(std::runtime_error re){
            qDebug() << "Could not find Process HTTP in Client::receivePackage receiving TCP Handshake Package from Server";
            return;
        }

        qInfo() << "Client: " << this->getNetworkCard().getNetworkAddress().getAddressAsDecString() << " sends 3. Handshake Package to router: " << router->getNetworkCard().getPhysicalAddress().getAddressAsString();
        router->receivePackage(httpProcess.getHandShakePackage(HeaderUtil::getIPAddressAsIPAddress(data,true),false,true));
    }

    //Receives a Closing Package from Server
    if(HeaderUtil::getTCPFlag(data, TCPFlag::FIN) == "Set" && HeaderUtil::getTCPFlag(data, TCPFlag::ACK) == "Set"){
        MACAddress routerMAC = this->getHostTable().value(HeaderUtil::getIPAddressAsIPAddress(data, true));
        Router* router;
        try{
            router = this->getRouterByMACAddress(routerMAC);
        }catch(CableNotFoundException cnfe){
            qDebug() << cnfe.getErrorMessage() << " in Client::receivePackage receiving the closing Package from Server";
            return;
        }
        if(router == nullptr){
            qDebug() << "Router is nullptr in Client::receivePackage";
            return;
        }

        Process httpProcess;
        try{
            httpProcess = getProcessByName("HTTP");
        }catch(std::runtime_error re){
            qDebug() << "Could not find Process HTTP in Client::receivePackage receiving a closing package from Server";
            return;
        }
        qInfo() << "Client: " << this->getNetworkCard().getNetworkAddress().getAddressAsDecString() << " sends 3. Handshake Package to router: " << router->getNetworkCard().getPhysicalAddress().getAddressAsString();
        router->receivePackage(httpProcess.getCloseConnectionPackage(HeaderUtil::getIPAddressAsIPAddress(data,true),false,true));
    }
}
