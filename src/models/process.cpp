#include "process.h"
#include "package.h"
#include "src/protocols/http.h"
#include "src/network/host.h"

Process::Process(Host* host, const Port &destinationPort) : host(host)
{
    openSocket(destinationPort);
}

void Process::openSocket(const Port &destinationPort){
    this->socket = Socket(0, destinationPort);
    socket.setSourcePort(Port::getRandomPort());
}

Package Process::getHTTPRequest(const QString &uri){
    IPAddress destination = host->getDomainTable()[uri].getAddressAsArray();
    Package data("Request HTML of " + uri);
    //Adding HTTP Header
    HTTP::initHTTPRequest("GET",uri,"HTTP/1.1",data);

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
    host->getNetworkCard().addMACHeader(data,host->getHostTable()[destination],0);
    return data;
}

Package Process::getHandShakePackage(const QString &url, bool initiate, bool client){
    //Client Handshakepackages
    if(initiate && client){
        IPAddress destinationAddress(host->getDomainTable()[url]);
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
        host->getNetworkCard().addMACHeader(tcpSynPackage,host->getHostTable()[destinationAddress],0);
        return tcpSynPackage;
    }
    else if(!initiate && client){
        IPAddress destinationAddress(host->getDomainTable()[url]);
        Package tcpACKPackage;
        socket.addTCPHeader(tcpACKPackage,
                            host->getNetworkCard().getNetworkAddress(),
                            destinationAddress,
                            true,
                            false,
                            false,
                            false);

        host->getNetworkCard().addIPHeader(tcpACKPackage,6,destinationAddress);
        host->getNetworkCard().addMACHeader(tcpACKPackage,host->getHostTable()[destinationAddress],0);
        return tcpACKPackage;
    }
    //TODO SERVER HANDSHAKEPACKAGES

}

Socket Process::getSocket(){
    return socket;
}
