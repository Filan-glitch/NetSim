#include "client.h"
#include "src/protocols/tcp.h"
#include "src/protocols/http.h"


Client::Client(const NetworkCard &networkCard) : Host(networkCard)
{}

Package Client::getHTTPRequest(const QString &url){
    IPAddress destination = this->getDomainTable().value(url);
    Package data;
    HTTP::initHTTPRequest("GET",url,"1.1",data);
    TCP::initHeader(this->getNetworkCard().getNetworkAddress(),
                    destination,
                    80,
                    80,
                    0,
                    0,
                    false,
                    false,
                    false,
                    false,
                    512,
                    data,
                    0);
    getNetworkCard().addIPHeader(data,6,destination);
    getNetworkCard().addMACHeader(data,this->getHostTable().value(destination),0);
    return data;
}

Package Client::getHandShakePackage(const QString &url, bool initiate){
    if(initiate){
        Package tcpSynPackage;
        IPAddress destinationAddress(this->getDomainTable().value(url));
        TCP::initHeader(this->getNetworkCard().getNetworkAddress(),
                        destinationAddress,
                        80,
                        80,
                        0,
                        0,
                        false,
                        false,
                        true,
                        false,
                        512,
                        tcpSynPackage,
                        0);

        getNetworkCard().addIPHeader(tcpSynPackage,6,destinationAddress);
        getNetworkCard().addMACHeader(tcpSynPackage,getHostTable().value(destinationAddress),0);
        return tcpSynPackage;
    }
    else{
        Package tcpACKPackage;
        IPAddress destinationAddress(this->getDomainTable().value(url));
        TCP::initHeader(this->getNetworkCard().getNetworkAddress(),
                        destinationAddress,
                        80,
                        80,
                        0,
                        0,
                        true,
                        false,
                        false,
                        false,
                        512,
                        tcpACKPackage,
                        0);

        getNetworkCard().addIPHeader(tcpACKPackage,6,destinationAddress);
        getNetworkCard().addMACHeader(tcpACKPackage,getHostTable().value(destinationAddress),0);
        return tcpACKPackage;
    }
}
