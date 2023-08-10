#include "process.h"
#include "package.h"
#include "src/network/client.h"
#include "src/protocols/http.h"
#include "src/network/host.h"
#include "src/protocols/dns.h"
#include "src/network/server.h"

Process::Process(const Port &destinationPort, const QString &name) : name(name)
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
    host->getNetworkCard().addMACHeader(data,host->getHostTable().value(destination), 2048);
    return data;
}

Package Process::getHandShakePackage(const IPAddress &address, bool initiate, bool client){
    //Client Handshakepackages
    if(initiate && client){
        Package tcpSynPackage("TCP Handshake [SYN]");

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
        host->getNetworkCard().addMACHeader(tcpSynPackage,host->getHostTable().value(address), 2048);
        return tcpSynPackage;
    }
    //Client 3. Handshakepackage
    else if(!initiate && client){
        Package tcpACKPackage("TCP Handshake [ACK]");
        socket.addTCPHeader(tcpACKPackage,
                            host->getNetworkCard().getNetworkAddress(),
                            address,
                            true,
                            false,
                            false,
                            false);

        host->getNetworkCard().addIPHeader(tcpACKPackage,6,address);
        host->getNetworkCard().addMACHeader(tcpACKPackage,host->getHostTable().value(address), 2048);
        return tcpACKPackage;
    }

    //Server Handshake Package
    if(!client){
        Package synAckPackage("TCP Handshake [SYN, ACK]");
        socket.addTCPHeader(synAckPackage,
                            host->getNetworkCard().getNetworkAddress(),
                            address,
                            true,
                            false,
                            true,
                            false);
        host->getNetworkCard().addIPHeader(synAckPackage,6,address);
        host->getNetworkCard().addMACHeader(synAckPackage,host->getHostTable().value(address), 2048);
        return synAckPackage;
    }

    return Package();
}

Package Process::getHTTPResponse(const IPAddress &destination, const Port &destPort, const int &messageCode){
    //Creating package
    Package data("HTTP Response to: " + destination.toString());

    //Adding HTTP Data
    if(messageCode == 200){
        HTTP::initHTTPResponse("HTTP/1.1",messageCode,"OK",data,static_cast<Server *>(host)->getHtmlFile());
    }
    else if(messageCode == 404){
        HTTP::initHTTPResponse("HTTP/1.1",messageCode,"Not Found",data,"");
    }
    else{
        qDebug() << "No valid messageCode in Process::getHTTPResponse messageCode: " << messageCode;
        return Package();
    }

    //Adding TCP Data
    socket.setDestinationPort(destPort);
    socket.addTCPHeader(data,host->getNetworkCard().getNetworkAddress(),destination,true,true,false,false);

    //Adding IP Data
    host->getNetworkCard().addIPHeader(data,6,destination);

    //Adding Ethernet II Data
    host->getNetworkCard().addMACHeader(data,host->getHostTable().value(destination), 2048);
    return data;
}

Package Process::getCloseConnectionPackage(const IPAddress &address, bool initiate, bool client){
    //Client Close Connection
    if(initiate && client){
        Package tcpFinPackage("TCP Connection Close [FIN]");

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
        host->getNetworkCard().addMACHeader(tcpFinPackage,host->getHostTable().value(address), 2048);
        return tcpFinPackage;
    }
    //Client 3. Handshakepackage
    else if(!initiate && client){
        Package tcpACKPackage("TCP Connection Close [ACK]");
        socket.addTCPHeader(tcpACKPackage,
                            host->getNetworkCard().getNetworkAddress(),
                            address,
                            true,
                            false,
                            false,
                            false);

        host->getNetworkCard().addIPHeader(tcpACKPackage,6,address);
        host->getNetworkCard().addMACHeader(tcpACKPackage,host->getHostTable().value(address), 2048);
        return tcpACKPackage;
    }

    //Server Handshake Package
    if(!client){
        Package finAckPackage("TCP Connection Close [FIN, ACK]");
        socket.addTCPHeader(finAckPackage,
                            host->getNetworkCard().getNetworkAddress(),
                            address,
                            true,
                            false,
                            false,
                            true);
        host->getNetworkCard().addIPHeader(finAckPackage,6,address);
        host->getNetworkCard().addMACHeader(finAckPackage,host->getHostTable().value(address), 2048);
        return finAckPackage;
    }

    return Package();
}

Package Process::getDNSRequest(const QString& domain) {
    Package package("DNS Request of domain: " + domain);

    DNS::initDNSRequest(package, QList<DNSEntry>() << DNSEntry(domain, 1, 1));

    socket.addUDPHeader(package);

    IPAddress dnsServer = host->getDomainTable().value(QString("dns.beispiel.de"));
    host->getNetworkCard().addIPHeader(package, 17, dnsServer);

    host->getNetworkCard().addMACHeader(package, host->getHostTable().value(dnsServer), 2048);

    return package;
}

Package Process::getDNSResponse(const IPAddress& address, const QString& domain, const Port &destPort) {
    Package package("DNS Response of domain: " + domain);

    DNS::initDNSResponse(package, QList<DNSEntry>() << DNSEntry(domain, 1, 1), QList<DNSEntry>() << DNSEntry(domain, 1, 1, 5600, host->getDomainTable().value(domain).getAddressAsArray()));

    socket.setDestinationPort(destPort);
    socket.addUDPHeader(package);

    host->getNetworkCard().addIPHeader(package, 17, address);

    host->getNetworkCard().addMACHeader(package, host->getHostTable().value(address), 2048);

    return package;
}

QString Process::getName() const
{
    return name;
}

void Process::setHost(Host *host)
{
    this->host = host;
}

QString Process::toString() const
{
    return QString("Name: %1 Port: %2").arg(name).arg(socket.getSourcePort().getPortNumber());
}

Socket& Process::getSocket(){
    return socket;
}
