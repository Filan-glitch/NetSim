#include "process.h"
#include "package.h"
#include "src/protocols/http.h"
#include "src/network/host.h"

#include <src/network/server.h>

Process::Process(Host* host, const Port &destinationPort) : host(host)
{
    openSocket(destinationPort);
}

void Process::openSocket(const Port &destinationPort){
    this->socket = Socket(0, destinationPort);
    socket.setSourcePort(Port::getRandomPort());
}

Package Process::getHTTPRequest(const QString &uri,const IPAddress &destination){
    Package data("Request HTML of " + uri);
    //Adding HTTP Header
    HTTP::initHTTPRequest("GET",uri,"HTTP/1.1",data);

    //Adding TCP Header
    socket.addTCPHeader(data,
                        host->getNetworkCard().getNetworkAddress(),
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

Package Process::getHandShakePackage(const IPAddress &address, bool initiate, bool client){
    //Client Handshakepackages
    if(initiate && client){
        Package tcpSynPackage;

        //Adding TCP Header
        socket.addTCPHeader(tcpSynPackage,
                            host->getNetworkCard().getNetworkAddress(),
                            address,
                            false,
                            false,
                            true,
                            false);

        //Adding IP Header
        host->getNetworkCard().addIPHeader(tcpSynPackage,6,address);

        //Adding Ethernet II Header
        host->getNetworkCard().addMACHeader(tcpSynPackage,host->getHostTable()[address],0);
        return tcpSynPackage;
    }
    //Client 3. Handshakepackage
    else if(!initiate && client){
        Package tcpACKPackage;
        socket.addTCPHeader(tcpACKPackage,
                            host->getNetworkCard().getNetworkAddress(),
                            address,
                            true,
                            false,
                            false,
                            false);

        host->getNetworkCard().addIPHeader(tcpACKPackage,6,address);
        host->getNetworkCard().addMACHeader(tcpACKPackage,host->getHostTable()[address],0);
        return tcpACKPackage;
    }

    //Server Handshake Package
    if(!client){
        Package synAckPackage;
        socket.addTCPHeader(synAckPackage,
                            host->getNetworkCard().getNetworkAddress(),
                            address,
                            true,
                            false,
                            true,
                            false);
        host->getNetworkCard().addIPHeader(synAckPackage,6,address);
        host->getNetworkCard().addMACHeader(synAckPackage,host->getHostTable()[address],0);
        return synAckPackage;
    }
}

Package Process::getHTTPResponse(const IPAddress &destination){
    //Creating package
    Package data("HTTP Response to: " + destination.getAddressAsDecString());

    //Adding HTTP Data
    HTTP::initHTTPResponse("HTTP/1.1",200,"OK",data,static_cast<Server *>(host)->getHtmlFile());

    //Adding TCP Data
    socket.addTCPHeader(data,host->getNetworkCard().getNetworkAddress(),destination,true,true,false,false);

    //Adding IP Data
    host->getNetworkCard().addIPHeader(data,6,destination);

    //Adding Ethernet II Data
    host->getNetworkCard().addMACHeader(data,host->getHostTable()[destination],static_cast<Server *>(host)->getHtmlFile().size());
    return data;
}

Package Process::getCloseConnectionPackage(const IPAddress &address, bool initiate, bool client){
    //Client Close Connection
    if(initiate && client){
        Package tcpFinPackage;

        //Adding TCP Header
        socket.addTCPHeader(tcpFinPackage,
                            host->getNetworkCard().getNetworkAddress(),
                            address,
                            false,
                            false,
                            false,
                            true);

        //Adding IP Header
        host->getNetworkCard().addIPHeader(tcpFinPackage,6,address);

        //Adding Ethernet II Header
        host->getNetworkCard().addMACHeader(tcpFinPackage,host->getHostTable()[address],0);
        return tcpFinPackage;
    }
    //Client 3. Handshakepackage
    else if(!initiate && client){
        Package tcpACKPackage;
        socket.addTCPHeader(tcpACKPackage,
                            host->getNetworkCard().getNetworkAddress(),
                            address,
                            true,
                            false,
                            false,
                            false);

        host->getNetworkCard().addIPHeader(tcpACKPackage,6,address);
        host->getNetworkCard().addMACHeader(tcpACKPackage,host->getHostTable()[address],0);
        return tcpACKPackage;
    }

    //Server Handshake Package
    if(!client){
        Package finAckPackage;
        socket.addTCPHeader(finAckPackage,
                            host->getNetworkCard().getNetworkAddress(),
                            address,
                            true,
                            false,
                            false,
                            true);
        host->getNetworkCard().addIPHeader(finAckPackage,6,address);
        host->getNetworkCard().addMACHeader(finAckPackage,host->getHostTable()[address],0);
        return finAckPackage;
    }
}

Socket Process::getSocket(){
    return socket;
}
