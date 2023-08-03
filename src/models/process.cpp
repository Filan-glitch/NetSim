#include "process.h"
#include "package.h"
#include "src/protocols/http.h"
#include "src/network/host.h"
#include "src/protocols/tcp.h"

Process::Process()
{

}

void Process::openSocket(const Port &sourcePort){
    this->socket = Socket(sourcePort, Port(80));
}

Package Process::getHTTPRequest(const QString &url){
    IPAddress destination = host->getDomainTable().value(url);
    Package data;
    //Adding HTTP Header
    HTTP::initHTTPRequest("GET",url,"1.1",data);

    //Adding TCP Header
    socket.addTCPHeader(data,host->getNetworkCard().getNetworkAddress(),
                        destination,
                        true,
                        true,
                        false,
                        false);

    //Adding IP Header
    host->getNetworkCard().addIPHeader(data,6,destination);

    //Adding Ethernet II Header
    host->getNetworkCard().addMACHeader(data,host->getHostTable().value(destination),0);
    return data;
}

Package Process::getHandShakePackage(const QString &url, bool initiate, bool client){
    //Client Handshakepackages
    if(initiate && client){
        IPAddress destinationAddress(host->getDomainTable().value(url));
        Package tcpSynPackage;

        //Adding TCP Header
        socket.addTCPHeader(tcpSynPackage,
                            host->getNetworkCard().getNetworkAddress(),
                            destinationAddress,
                            false,
                            false,
                            true,
                            false);

        //Adding IP Header
        host->getNetworkCard().addIPHeader(tcpSynPackage,6,destinationAddress);

        //Adding Ethernet II Header
        host->getNetworkCard().addMACHeader(tcpSynPackage,host->getHostTable().value(destinationAddress),0);
        return tcpSynPackage;
    }
    else if(!initiate && client){
        IPAddress destinationAddress(host->getDomainTable().value(url));
        Package tcpACKPackage;
        socket.addTCPHeader(tcpACKPackage,
                            host->getNetworkCard().getNetworkAddress(),
                            destinationAddress,
                            true,
                            false,
                            false,
                            false);

        host->getNetworkCard().addIPHeader(tcpACKPackage,6,destinationAddress);
        host->getNetworkCard().addMACHeader(tcpACKPackage,host->getHostTable().value(destinationAddress),0);
        return tcpACKPackage;
    }
    //TODO SERVER HANDSHAKEPACKAGES

}
