#include "server.h"
#include "router.h"
#include "cablenotfoundexception.h"

#include <src/protocols/headerutil.h>


Server::Server(const NetworkCard &networkCard, const QString &domain) : Host(networkCard), m_domain(domain)
{
}

QString Server::domain() const
{
    return m_domain;
}

QString Server::getHtmlFile()const{
    return this->htmlFile;
}

void Server::receivePackage(Package data){
    qInfo() << "Server: " << this->getNetworkCard().getNetworkAddress().toString() << " received a Package: " << data.getInfo();
    getPackages()->addPackage(data);

    //Receives a DNS Request Package
    if(HeaderUtil::getApplicationProtocol(data) == HeaderType::DNS) {
        //Getting the DNS process
        Process dnsProcess;
        try{
            dnsProcess = getProcessByName("DNS");
        }catch(std::runtime_error re){
            qDebug() << "Could not find Process DNS in Server::receivePackage DNS Request Package";
            return;
        }


        //Creating the response package for dns request
        Package dnsResponse = dnsProcess.getDNSResponse(HeaderUtil::getIPAddressAsIPAddress(data, true), HeaderUtil::getDNSQuery(data, 0, RRAttribute::NAME), HeaderUtil::getPortAsPort(data, true));

        //Getting the local Router
        MACAddress routerMAC = this->getHostTable().value(HeaderUtil::getIPAddressAsIPAddress(data, true));
        Router* router;
        try{
            router = this->getRouterByMACAddress(routerMAC);
        }catch(CableNotFoundException cnfe){
            qDebug() << cnfe.getErrorMessage() << " in Server::receivePackage creating DNS Response";
            return;
        }

        if(router == nullptr){
            qDebug() << "Router is nullptr in Server::receivePackage";
            return;
        }

        //Sending package to local Router
        qInfo() << "Server: " << this->getNetworkCard().getNetworkAddress().toString() << " sends DNSResponse to Router: " << router->getNetworkCard().getPhysicalAddress().toString();
        router->receivePackage(dnsResponse);
        return;

    }

    //Receives a TCP Handshake Package
    if(HeaderUtil::getTCPFlag(data,TCPFlag::SYN) == "Set"){
        //Getting the HTTP Process
        Process httpProcess;
        try{
            httpProcess = getProcessByName("HTTP");
        }catch(std::runtime_error re){
            qDebug() << "Could not find HTTP Process in Server::receivePackage TCP Handshake Package";
        }

        httpProcess.getSocket().setDestinationPort(HeaderUtil::getPortAsPort(data, false));

        //Creating the response Package for TCP Handshake
        Package synAckPackage = httpProcess.getHandShakePackage(HeaderUtil::getIPAddressAsIPAddress(data,true),false,false);

        //Getting the local Router
        MACAddress routerMAC = this->getHostTable().value(HeaderUtil::getIPAddressAsIPAddress(data, true));
        Router* router;
        try{
            router = this->getRouterByMACAddress(routerMAC);
        }catch(CableNotFoundException cnfe){
            qDebug() << cnfe.getErrorMessage() << " in Server::receivePackage receiving TCP Handshakepackage";
            return;
        }

        if(router == nullptr){
            qDebug() << "Router is nullptr in Server::receivePackage";
            return;
        }

        //Sending package to local Router
        qInfo() << "Server: " << this->getNetworkCard().getNetworkAddress().toString() << " sends SYNACK Package to Router: " << router->getNetworkCard().getPhysicalAddress().toString();
        router->receivePackage(synAckPackage);
        return;
    }

    //Connection close
    if(HeaderUtil::getTCPFlag(data,TCPFlag::FIN) == "Set"){
        //Getting the HTTP Process
        Process httpProcess;
        try{
            httpProcess = getProcessByName("HTTP");
        }catch(std::runtime_error re){
            qDebug() << "Process HTTP not found in: Server::receivePackage connection close";
            return;
        }


        //Creating the response Package for close connection
        Package synAckPackage = httpProcess.getCloseConnectionPackage(HeaderUtil::getIPAddressAsIPAddress(data,true),false,false);

        //Getting the local Router
        MACAddress routerMAC = this->getHostTable().value(HeaderUtil::getIPAddressAsIPAddress(data, true));
        Router* router;
        try{
            router = this->getRouterByMACAddress(routerMAC);
        }catch(CableNotFoundException cnfe){
            qDebug() << cnfe.getErrorMessage() << " in Server::receivePackage creating the closeConnection Response";
            return;
        }

        if(router == nullptr){
            qDebug() << "Router is nullptr in Server::receivePackage";
            return;
        }

        //Sending package to local Router
        qInfo() << "Server: " << this->getNetworkCard().getNetworkAddress().toString() << " sends FINACK Package to router: " << router->getNetworkCard().getPhysicalAddress().toString();
        router->receivePackage(synAckPackage);
        return;
    }

    //HTTP Response Message
    if(HeaderUtil::getHTTPIsRequest(data)){
        //Getting the HTTP Process
        Process httpProcess;
        try{
            httpProcess = getProcessByName("HTTP");
        }catch(std::runtime_error re){
            qDebug() << "Could not find Process HTTP in: HeaderUtil::getHTTPIsRequest";
            return;
        }


        //Creating the HTTP Response Package
        Package httpResponse;
        if(HeaderUtil::getHTTPAttribute(data,"URI") == "/index.html"){
            httpResponse = httpProcess.getHTTPResponse(HeaderUtil::getIPAddressAsIPAddress(data,true), HeaderUtil::getPortAsPort(data, true),200);
        }else{
            httpResponse = httpProcess.getHTTPResponse(HeaderUtil::getIPAddressAsIPAddress(data,true), HeaderUtil::getPortAsPort(data, true),404);
        }

        //Getting the local Router
        MACAddress routerMAC = this->getHostTable().value(HeaderUtil::getIPAddressAsIPAddress(data, true));
        Router* router;
        try{
            router = this->getRouterByMACAddress(routerMAC);
        }catch(CableNotFoundException cnfe){
            qDebug() << cnfe.getErrorMessage() << " in Server::receivePackage creating HTTP Response";
            return;
        }

        if(router == nullptr){
            qDebug() << "Router is nullptr in Server::receivePackage";
            return;
        }

        //Sending package to local Router
        qInfo() << "Server: " << this->getNetworkCard().getNetworkAddress().toString() << " sends HTTP Response to router: " << router->getNetworkCard().getPhysicalAddress().toString();
        router->receivePackage(httpResponse);
        return;
    }

}
